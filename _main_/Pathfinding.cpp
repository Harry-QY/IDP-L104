#include "Pathfinding.h"
#include "Arduino.h"
#include "MotorControl.h"
#include "LineSensorCombinations.h"
#include "DFRobot_VL53L0X.h"
#include "BlockDetection.h"
#include "LEDControl.h"

#define ls 6 // left sensor
#define rs 7 // right sensor
#define fs 8 // front sensor
#define bs 9 // back sensor
#define btn 3 // button
#define blueLED 4 // blue LED
#define MAX_RANG (520)//the max measurement value of the module is 520cm(a little bit longer than effective max range)
#define ADC_SOLUTION (1023.0)//ADC accuracy of Arduino UNO is 10bit

#define sensingPin A0 //for UltraSonic (US)

int lsv, rsv, fsv, bsv; //binary value for line sensor readings
int start = 0; //start defined as 'extern' such that it can be set in here, stopping main loop in .ino
int Odometry = 0;

void FollowPath(int (*current_path)[3], char* current_actions, int path_size) {

    int i = 0;
    Serial.print("Loop starts. Path size = ");
    Serial.println(path_size);
    onblueLEDsequence();

    while (i < path_size) {
        lsv = digitalRead(ls);
        rsv = digitalRead(rs);
        fsv = digitalRead(fs);
        bsv = digitalRead(bs); //read all line sensor states
        blueLEDticker.update(); //required to flip LED. Works different to the .detach() function we used in for coursework since those only work with ARM stuff.
        int SensorState = lineSensorStates(lsv, rsv, fsv, bsv); //interpret line following states

        
        if (SensorState == current_path[i][0] || SensorState == current_path[i][1] || SensorState == current_path[i][2]) {
            Serial.print("Feature detected: "); //if sensor states indicate junction, take associated action
            Serial.print(i);
            Serial.print("; Action: ");
            Serial.println(current_actions[i]);
            MotorAction(current_actions[i]);
            Serial.print("Move on to junction: ");
            Serial.println(i+1);
            // Update i to move to the next element in the path
            i++;
        } 
        else {
            // Perform straight line following
            // Serial.print("Go straight, sensor state:"); Serial.println(SensorState); 
            LineFollow(SensorState);
        } 
        if (digitalRead(btn) == 1) {
            Serial.println("Stop");
            delay(500);
            start = !start;
            break; //break this loop and set start = 0 to break _main_.ino loop
        }
    }
    offblueLEDsequence();
}

void BlockFinding() {
    DetectionSensorsSetup();
    throttle = 0.5; //forward speed factor
    float ToF = 10000;
    while (ToF > 75) { //line follow until ToF reads less than 76
        ToF = sensor.getDistance();
        Serial.print("ToF reading: ");
        Serial.println(ToF);
        lsv = digitalRead(ls);
        rsv = digitalRead(rs);
        fsv = digitalRead(fs);
        bsv = digitalRead(bs);
        blueLEDticker.update(); //required to flip LED. Works different to the .detach() function we used in for coursework since those only work with ARM stuff.
        int SensorState = lineSensorStates(lsv, rsv, fsv, bsv); //read sensor states
        LineFollow(SensorState); //interpret states and line follow forward, at throttled speed
    }
    MotorOff();
    throttle = 1;
};

void PlatformFinding() {
    DetectionSensorsSetup();
    throttle = 0.5;
    float US = 10000;
    while ((US > 13) && (US > 0)) { //US sometimes gives -ve readings, requires logical and (&&) 
      int t = analogRead(sensingPin);
      // get distances
      US = t * MAX_RANG / ADC_SOLUTION;//
      Serial.print("US reading: ");
      Serial.println(US);
      lsv = digitalRead(ls);
      rsv = digitalRead(rs);
      fsv = digitalRead(fs);
      bsv = digitalRead(bs);
      int SensorState = lineSensorStates(lsv, rsv, fsv, bsv);
      LineFollow(SensorState); //line follow at throttled speed if no platform found

      if (digitalRead(btn) == 1) {
        Serial.println("Stop");
        delay(500);
        start = !start;
        break;
      }
    }
    Serial.println("About to go forward for 1s");
    MotorForward(120, 1000); //This is required since UltraSonic detects platform lip, so need to move forward a bit to reach edge
    throttle = 1;
    MotorOff();
};

void IndustrialBlockFinding() {
    while (Odometry < 20000) {
        lsv = digitalRead(ls);
        rsv = digitalRead(rs);
        fsv = digitalRead(fs);
        bsv = digitalRead(bs);
        int SensorState = lineSensorStates(lsv, rsv, fsv, bsv);
        LineFollow(SensorState);
    }
    MotorAction("L");
    MotorForward(150,1000);
    // scans for the block
    float ToF = 10000;
    int swing_time = 0;
    while (ToF > 100 && swing_time < 1000) { //line follow until ToF reads less than 100
        ToF = sensor.getDistance();
        MotorLeft(150, 100);
    }
    while (ToF > 100 && swing_time < 2000) { //line follow until ToF reads less than 100
        ToF = sensor.getDistance();
        MotorRight(150, 100);
    }
    while (ToF > 50) {
        ToF = sensor.getDistance();
        MotorForward(100,200);
    }
}

void IndustrialPathFinding() {
    onblueLEDsequence();
    MotorAction('T');
    int SensorState = 0;
    while (SensorState  == 0) {
        lsv = digitalRead(ls);
        rsv = digitalRead(rs);
        fsv = digitalRead(fs);
        bsv = digitalRead(bs); //read all line sensor states
        blueLEDticker.update(); //required to flip LED. Works different to the .detach() function we used in for coursework since those only work with ARM stuff.
        SensorState = lineSensorStates(lsv, rsv, fsv, bsv); //interpret line following states
        MotorForward(150,200);
    }
    MotorAction('R');
}
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

int lsv, rsv, fsv, bsv;

DFRobot_VL53L0X sensor0;

void FollowPath(int (*current_path)[3], char* current_actions, int path_size) {

    int i = 0;
    Serial.print("Loop starts. Path size = ");
    Serial.println(path_size);
    onblueLEDsequence();

    while (i < path_size) {
        lsv = digitalRead(ls);
        rsv = digitalRead(rs);
        fsv = digitalRead(fs);
        bsv = digitalRead(bs);
        blueLEDticker.update(); //required to flip LED. Works different to the .detach() function we used in for coursework since those only work with ARM stuff.
        int SensorState = lineSensorStates(lsv, rsv, fsv, bsv);

        
        if (SensorState == (current_path[i][0] || current_path[i][2] || current_path[i][1])) {
            // Perform action here
            Serial.print("Feature detected: ");
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
            Serial.print("Go straight, sensor state:");   
            Serial.println(SensorState); 
            LineFollow(SensorState);
        } 
        if (digitalRead(btn) == 1) {
            Serial.println("Stop");
            delay(500);
            break;
        }
    }
    offblueLEDsequence();
}

void BlockFinding() {
    DetectionSensorsSetup();
    float ToF = 100;
    while (ToF > 50) {
        ToF = sensor0.getDistance();
        lsv = digitalRead(ls);
        rsv = digitalRead(rs);
        fsv = digitalRead(fs);
        bsv = digitalRead(bs);
        blueLEDticker.update(); //required to flip LED. Works different to the .detach() function we used in for coursework since those only work with ARM stuff.
        int SensorState = lineSensorStates(lsv, rsv, fsv, bsv);
        LineFollow(SensorState);

    }
    MotorOff();
};

void PlatformFinding() {
    DetectionSensorsSetup();
    float US = 100;
    while (US > 50) {
    int t = analogRead(sensingPin);
    // get distances
    US = t * MAX_RANG / ADC_SOLUTION;//
    lsv = digitalRead(ls);
    rsv = digitalRead(rs);
    fsv = digitalRead(fs);
    bsv = digitalRead(bs);
    int SensorState = lineSensorStates(lsv, rsv, fsv, bsv);
    LineFollow(SensorState);
    }
    MotorOff();
};
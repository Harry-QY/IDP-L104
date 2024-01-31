#include <Adafruit_MotorShield.h> //header file for protecting motors
#include "MotorControl.h"
#include "Pathfinding.h"
#include "LineSensorCombinations.h"

#define ls 6 // left sensor
#define rs 7 // right sensor
#define fs 8 // front sensor
#define bs 9 // back sensor

int lsv, rsv, fsv, bsv;
int btn = 3; //sets button

int start = 0;
int mode = 0;

void setup() {
  pinMode(btn, INPUT);  // declare pushbutton as input
  MotorSetup();
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ls, INPUT);
  pinMode(rs, INPUT);
  pinMode(fs, INPUT);
  pinMode(bs, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // 0 for going straight, L for left junction, R for right junction, F for front junction and B for back junction
  if (digitalRead(btn) == 1) {
    start = !start;
    delay(500);
    Serial.print("Button pressed, robot is in state: ");
    Serial.println(start);
  }

  while (start == 1) {
    // put your main code here, to run repeatedly:
    int path1[5] = {0, 8, 14, 10}; // looks for start box, inverse T, T, right hand junction, end of line
    char actions1[] = "FFLRS";
    /*
    int path2a[];
    char actions2a[];
    int path2b[];
    char actions2b[];
    int path3a[];
    char path3a[];
    int path3b[];
    char path3b[];
    */

    int pick_drop = 0; // 0 for picking up, 1 for dropping off
    int num_delivered = 0; // number of block delivered

    int* current_path = path1;
    char* current_actions = actions1;
    int path_size = sizeof(path1)/sizeof(int);
    int i = 0;
    Serial.print("Loop starts. ");

    while (i < path_size) {
    lsv = digitalRead(ls);
    rsv = digitalRead(rs);
    fsv = digitalRead(fs);
    bsv = digitalRead(bs);
    int SensorState = lineSensorStates(lsv, rsv, fsv, bsv);

    if (SensorState == current_path[i]) {
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
    } else {
        // Perform straight line following
        Serial.print("Go straight, sensor state:");   
        Serial.println(SensorState); 
        LineFollow(SensorState);
    }

    if (digitalRead(btn) == 1) {
      start = !start;
      delay(500);
      Serial.print("Button pressed, robot is in state: ");
      Serial.println(start);
      break;
    }

    // block detection
    // pick/drop block, switch pick/drop mode
    // update current path based on block type
    // drop block, num_delivered += 1
  }
    
  }
}

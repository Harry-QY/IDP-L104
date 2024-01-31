#include <Adafruit_MotorShield.h> //header file for protecting motors
#include "MotorControl.h"
#include "Pathfinding.h"
#include "LineSensorCombinations.h"


#define ls 6 // left sensor
#define rs 7 // right sensor
#define fs 8 // front sensor
#define bs 9 // back sensor

// int lsv, rsv, fsv, bsv;

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
    int path1[] = {0, 8, 14, 10, 4}; // looks for start box, inverse T, T, right hand junction, end of line
    char actions1[] = "FFLRS";
    int path2a[] = {7, 8, 14, 4}; // go to green
    char actions2a[] = "BLLS";
    int path2b[] = {7, 8, 10, 14, 4}; // go to red
    char actions2b[] = "BRFRS";
    int path3a[] = {9, 10, 9, 10, 4}; // go to next block from green
    char actions3a[] = "TRFRS"; 
    int path3b[] = {10, 9, 9, 4}; // go to next block from red
    char actions3b[] = "TLLS";

    int pick_drop = 0; // 0 for picking up, 1 for dropping off
    int num_delivered = 0; // number of block delivered

    //int* current_path = path1;
    //char* current_actions = actions1;

    // follow path
    FollowPath(path1, actions1);

    // block detection
    // pick/drop block, switch pick/drop mode
    // update current path based on block type
    // drop block, num_delivered += 1
    
  }

    /*
    int path_size = sizeof(*current_path)/sizeof(int);
    int i = 0;
    Serial.print("Loop starts. Path size = ");
    Serial.println(path_size);

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
    */
}
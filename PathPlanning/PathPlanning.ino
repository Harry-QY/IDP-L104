#include <Adafruit_MotorShield.h> //header file for protecting motors
#include "MotorControl.h"
#include "Pathfinding.h"
#include "LineSensorCombinations.h"


#define ls 6 // left sensor
#define rs 7 // right sensor
#define fs 8 // front sensor
#define bs 9 // back sensor

// int lsv, rsv, fsv, bsv;

#define btn 3 //sets button

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

int btn_count = 0;

void loop() {
  // put your main code here, to run repeatedly:
  // 0 for going straight, L for left junction, R for right junction, F for front junction and B for back junction

  if (digitalRead(btn) == 1) {
    start = !start;
    delay(500);

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

    int* current_path = path1;
    char* current_actions = actions1;
    int path_size = sizeof(path1)/sizeof(int);

    // follow path
    FollowPath(current_path, current_actions, path_size);
    MotorOff();

    start = !start;

    // block detection
    // pick/drop block, switch pick/drop mode
    // update current path based on block type
    // drop block, num_delivered += 1
    
  }
}
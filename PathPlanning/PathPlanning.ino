#include <Adafruit_MotorShield.h> //header file for protecting motors
#include "MotorControl.h"
#include "Pathfinding.h"
#include "LineSensorCombinations.h"
#include "BlockDetection.h"
#include "LEDControl.h"

#define ls 6 // left sensor
#define rs 7 // right sensor
#define fs 8 // front sensor
#define bs 9 // back sensor
#define blueLED 4

// int lsv, rsv, fsv, bsv;

#define btn 3 //sets button

int path1[] = {0, 14, 10}; // looks for start box, inverse T, T, right hand junction, end of line
char actions1[] = "FLR";
int path2a[] = {7, 14, 14}; // go to green
char actions2a[] = "TLL";
int path2b[] = {7, 8, 14, 14}; // go to red
char actions2b[] = "TRFR";
int path3a[] = {9, 10, 9, 10}; // go to next block from green
char actions3a[] = "TRFR"; 
int path3b[] = {10, 9, 9}; // go to next block from red
char actions3b[] = "TLL";

int start = 0;
int mode = 0;

void setup() {
  pinMode(btn, INPUT);  // declare pushbutton as input
  pinMode(blueLED, OUTPUT);
  MotorSetup();
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ls, INPUT);
  pinMode(rs, INPUT);
  pinMode(fs, INPUT);
  pinMode(bs, INPUT);




  Serial.println("Finished setup");
}


void loop() {
  // put your main code here, to run repeatedly:
  // 0 for going straight, L for left junction, R for right junction, F for front junction and B for back junction

  if (digitalRead(btn) == 1) {
    start = !start;
    delay(500);
  }

  while (start == 1) {
    // put your main code here, to run repeatedly:

    int pick_drop = 0; // 0 for picking up, 1 for dropping off
    int num_delivered = 0; // number of block delivered

    int* current_path = path1;
    char* current_actions = actions1;
    int path_size = sizeof(path1)/sizeof(int);
    // follow path
    FollowPath(current_path, current_actions, path_size);
    MotorOff();
    start = !start;
    /*
    // block finding
    BlockFinding();
    // block detection
    int chosen_block = BlockIdentification();
    // pick/drop block, switch pick/drop mode

    if (chosen_block == 1) {
      int* current_path = path2a;
      char* current_actions = actions2a;
      int path_size = sizeof(path2a)/sizeof(int);
    } else {
      int* current_path = path2a;
      char* current_actions = actions2a;
      int path_size = sizeof(path2a)/sizeof(int);
    }

    // go to the selected platform
    FollowPath(current_path, current_actions, path_size);
    */


    // update current path based on block type
    // drop block, num_delivered += 1
    
  }

}
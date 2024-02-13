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

int path1[][3] = {{0,12,0}, {8,8,12}, {14,14,12}, {10,8,14}}; // looks for start box, inverse T, T, right hand junction, end of line
char actions1[] = "FFlR"; //to initial block

int path2green[][3] = {{14,14,12}, {14,14,12}}; // go to green
char actions2green[] = "Rl"; //to green drop off
int path2red[][3] = {{14,14,12},  {10,8,14}, {14,14,12}}; // go to red
char actions2red[] = "LFr"; //to red drop off

int path3green[][3] = {{10,8,14}, {10,8,14}, {9,8,14}, {10,8,14}}; // go to next block from green
char actions3green[] = "FRFR"; //to second (further) block from green drop off
int path3red[][3] = {{9,8,14}, {9,8,14}, {9,8,14}}; // go to next block from red
char actions3red[] = "FLL"; //to second (further) block from red drop off

int path4green[][3] = {{14,14,12}, {10,8,14}, {9,8,14}, {9,8,14}}; // block 2 to green
char actions4green[] = "LFlF";
int path4red[][3] = {{14,14,12}, {14,14,12}, {10,8,14}}; // block 2 to red
char actions4red[] = "RrF";

int path5green[][3] = {{10,8,14}, {10,8,14}, {9,8,14}}; // green to left industrial zone
char actions5green[] = "FRL";
int path5red[][3] = {{9,8,14}, {9,8,14}, {9,8,14}, {10,8,14}}; // red to left industiral zone
char actions5red[] = "FLFR";

int path6green[][3] = {{14,14,12}, {9,8,14}, {9,8,14}}; // left industiral zone to green
char actions6green[] = "rlF";
int path6red[][3] = {{14,14,12}, {10,8,14}, {14,14,12}, {10,8,14}}; // red to right industrial zone
char actions6red[] = "lFrF";

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
    int (*current_path)[3] = path1;
    char* current_actions = actions1;
    int path_size = sizeof(path1)/(3*sizeof(int)); //Used as input for FollowPath, until found all path junctions. path_size in bytes.
    // follow path
    FollowPath(current_path, current_actions, path_size); //Follows path, looking for junction. If a junction isnt found just linefollows.

    int chosen_block = 0;
    while (chosen_block == 0){
      BlockFinding(); //use ToF sensor to find block. End once a block is detected
      chosen_block = BlockIdentification(); //int returned indicates block type
    }
    ClampAndLift(); //clamp block, then lift

    if (chosen_block == 1) {
      Serial.print("Set path green.");
      current_path = path2green; //set new path to green platform
      current_actions = actions2green;
      path_size = sizeof(path2green)/(3*sizeof(int));
      MotorAction('T'); //turn 180 degrees
    } else {
      Serial.print("Set path red.");
      current_path = path2red; //set new path to red platform
      current_actions = actions2red;
      path_size = sizeof(path2red)/(3*sizeof(int));
      MotorAction('T'); //turn 180 degrees
    }
    // follow path
    FollowPath(current_path, current_actions, path_size);
    PlatformFinding();
    DescendAndRelease();
    // drop block, num_delivered += 1
  
    //At platform, go for second block----------------------------------

    if (chosen_block == 1) {
      Serial.print("Set green to new block.");
      current_path = path3green;
      current_actions = actions3green;
      path_size = sizeof(path3green)/(3*sizeof(int));
      MotorAction('T');
    } else {
      Serial.print("Set path red to new block.");
      current_path = path3red;
      current_actions = actions3red;
      path_size = sizeof(path3red)/(3*sizeof(int));
      MotorAction('T');
    }

    FollowPath(current_path, current_actions, path_size); //Follows path, looking for junction. If a junction isnt found just linefollows.

    // block finding    
    // block detection
    chosen_block = 0;
    while (chosen_block == 0){
      BlockFinding();
      chosen_block = BlockIdentification();
    }
    // pick/drop block, switch pick/drop mode
    ClampAndLift();
    if (chosen_block == 1) {
      Serial.print("Set path to green platform from futher block.");
      current_path = path4green;
      current_actions = actions4green;
      path_size = sizeof(path4green)/(3*sizeof(int));
      MotorAction('T');
    } else {
      Serial.print("Set path to red platform from futher block.");
      current_path = path4red;
      current_actions = actions4red;
      path_size = sizeof(path4red)/(3*sizeof(int));
      MotorAction('T');
    }
    // follow path
    FollowPath(current_path, current_actions, path_size);
    PlatformFinding();
    DescendAndRelease();

    MotorOff();
    offblueLEDsequence(); //turns off oscilating blue led
    start = 0;
  }
}
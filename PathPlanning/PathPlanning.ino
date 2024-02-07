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

int path1[][3] = {{0,12,0}, {14,14,12}, {10,8,14}}; // looks for start box, inverse T, T, right hand junction, end of line
char actions1[] = "FLR"; //to initial block
int path2green[][3] = {{7,7,7}, {14,14,12}, {14,14,12}}; // go to green
char actions2green[] = "TRL"; //to green drop off
int path2red[][3] = {{7,7,7}, {10,8,14}, {14,14,12}, {14,14,12}}; // go to red
char actions2red[] = "TLFR"; //to red drop off
int path3green[][3] = {{7,7,7}, {10,8,14}, {10,8,14}, {9,8,14}, {10,8,14}}; // go to next block from green
char actions3green[] = "TFRFR"; //to second (further) block from green drop off
int path3red[][3] = {{7,7,7}, {9,8,14}, {9,8,14}, {9,8,14}}; // go to next block from red
char actions3red[] = "TFLL"; //to second (further) block from red drop off

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

    int pick_drop = 0; // 0 for picking up, 1 for dropping off
    int num_delivered = 0; // number of block delivered

    int (*current_path)[3] = path1;
    char* current_actions = actions1;
    int path_size = sizeof(path1)/(3*sizeof(int)); //Used as input for FollowPath, until found all path junctions. path_size in bytes.
    // follow path
    //Serial.println("Running path1");
    //FollowPath(current_path, current_actions, path_size); //Follows path, looking for junction. If a junction isnt found just linefollows.

    // block finding
    BlockFinding();
    
    // block detection
    int chosen_block = 0;
    chosen_block = BlockIdentification();
    /*
    // pick/drop block, switch pick/drop mode
    if (chosen_block == 1) {
      (*current_path)[3] = path2green;
      * current_actions = actions2green;
      path_size = sizeof(path2green)/(3*sizeof(int));
    } else {
      (*current_path)[3] = path2red;
      * current_actions = actions2red;
      path_size = sizeof(path2red)/(3*sizeof(int));
    }

    (*current_path)[3] = path2green;
    * current_actions = actions2green;
    // follow path
    Serial.println("Running path2");
    FollowPath(current_path, current_actions, 3);
    start = !start;
    */
    // drop block, num_delivered += 1
  }
}
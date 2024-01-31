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

int fwd_speed = 230;
int fwd_time = 100;
int turn_speed = 100;
int turn_time = 100;

int start = 0;
int mode = 0;


float US_dist, sensing_t, ToF_dist;
int time_delay = 50;
int block_list[num_iterations];
int current_iteration = 0;
bool block_detected = false;
bool want_to_detect = true;
int block_type;
int chosen_block;

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

  if (start == 1) {
    // put your main code here, to run repeatedly:
    int path1[4] = {8, 14, 10, 4}; // looks for inverse T, T, right hand junction, end



    String actions1[4] = {"Forward", "Turn Left", "Turn right", "Stop"};
    int* current_path = path1;
    String* current_action = actions1;
    int path_size = sizeof(current_path)/sizeof(int);
    int i = 0;

    while (i < path_size) {
    lsv = digitalRead(ls);
    rsv = digitalRead(rs);
    fsv = digitalRead(fs);
    bsv = digitalRead(bs);
    int SensorState = lineSensorStates(lsv, fsv, rsv, bsv);

    if (SensorState == current_path[i]) {
        // Perform action here
        Serial.print("Junction ");
        Serial.print(i);
        Serial.print(" detected, performing action: ");
        Serial.print(actions1[i]);
        // Update i to move to the next element in the path
        i++;
    } else {
        // Go forward or perform other actions here if needed
    }
  }
    // picks up new path based on block type
}
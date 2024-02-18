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

int path4green[][3] = {{14,14,12}, {10,8,14}, {9,8,14}, {9,8,14}}; // block 2 from green
char actions4green[] = "LFlF";
int path4red[][3] = {{14,14,12}, {14,14,12}, {10,8,14}}; // block 2 from red
char actions4red[] = "RrF";
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
    PlatformFinding();
    Serial.println("Platform found");
    start = 0;
  }
}
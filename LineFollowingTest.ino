#include <Adafruit_MotorShield.h> //header file for protecting motors
#include "motorControl.h"

#define ls 1 // left sensor
#define rs 2 // right sensor
#define fs 3 // front sensor
#define bs 4 // back sensor

int lsv, rsv, fsv, bsv;
int btn = 0;
// to be adjusted
int fwd_speed = 150;
int fwd_time = 100;
int turn_speed = 50;
int turn_time = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(ls, INPUT);
  pinMode(rs, INPUT);
  pinMode(fs, INPUT);
  pinMode(bs, INPUT);
}

void loop() {
  while (digitalRead(btn) == 1) {
  // put your main code here, to run repeatedly:
  lsv = digitalRead(ls);
  rsv = digitalRead(rs);
  fsv = digitalRead(fs);
  bsv = digitalRead(bs);

  if (lsv == 0 & rsv == 0) {
  // go straight
    motorForward(fwd_speed, fwd_time);
  }
  if (lsv == 0 & rsv == 1) {
  // turn right
    motorRight(turn_speed, turn_time);
  }
  if (lsv == 1 & rsv == 0) {
  // turn left
    motorRight(turn_speed, turn_time);
  }
  }
}
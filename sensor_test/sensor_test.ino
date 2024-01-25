#include <Adafruit_MotorShield.h> //header file for protecting motors
#include "motorControl.h"

#define ls 6 // left sensor
#define rs 7 // right sensor
#define fs 8 // front sensor
#define bs 9 // back sensor

int lsv, rsv, fsv, bsv;
int btn = 3; //sets button
// to be adjusted
int fwd_speed = 150;
int fwd_time = 5000;
int turn_speed = 50;
int turn_time = 5000;
int start = 0; //has button been pressed?

void setup() {
  pinMode(btn, INPUT);  // declare pushbutton as input
  motorSetup();

  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ls, INPUT);
  pinMode(rs, INPUT);
  pinMode(fs, INPUT);
  pinMode(bs, INPUT);
}

void loop() {
  if (digitalRead(btn) == 1) {
    start = 1;
  }

  if (start == 1) {
    // put your main code here, to run repeatedly:
    lsv = digitalRead(ls);
    rsv = digitalRead(rs);
    fsv = digitalRead(fs);
    bsv = digitalRead(bs);

    Serial.print(lsv);
    Serial.print(rsv);
    Serial.print(fsv);
    Serial.println(bsv);
  }
}
#include <Adafruit_MotorShield.h> //header file for protecting motors
#include "driveMotorControl.h"
#include "liftControl.h"

#define ls 6 // left sensor
#define rs 7 // right sensor
#define fs 8 // front sensor
#define bs 9 // back sensor

int lsv, rsv, fsv, bsv;
int btn = 3; //sets button
// to be adjusted
int fwd_speed = 150;
int fwd_time = 100;
int turn_speed = 150;
int turn_time = 100;
int start = 0; //has button been pressed?

void setup() {
  pinMode(btn, INPUT);  // declare pushbutton as input
  driveMotorSetup();
  liftSetup();

  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ls, INPUT);
  pinMode(rs, INPUT);
  pinMode(fs, INPUT);
  pinMode(bs, INPUT);
}

void loop() {
  if (digitalRead(btn) == 1) {
    start = !start;
    delay(500);
    Serial.print("Button pressed, robot is in state: ");
    Serial.println(start);

    //raise lift motor
    liftMotorLower(50,5000);
    liftMotorRaise(50,5000);
  }

  if (start == 1) {
    // put your main code here, to run repeatedly:
    lsv = digitalRead(ls);
    rsv = digitalRead(rs);
    fsv = digitalRead(fs);
    bsv = digitalRead(bs);
    delay(10);

    if (lsv == 1 and rsv == 1) {
      Serial.println("both 1");
    }

    if (lsv == 0 and rsv == 0) {
      Serial.println("should go straight");
      // go straight
      motorForward(fwd_speed, fwd_time);
    }

    if (lsv == 0 and rsv == 1) {
      Serial.println("should go right");
      // turn right
      motorRight(turn_speed, turn_time);
    }

    if (lsv == 1 and rsv == 0) {
      // turn left
      Serial.println("should go left");
      motorLeft(turn_speed, turn_time);
    }
  }
}
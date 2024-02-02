#include <Adafruit_MotorShield.h>
#include "MotorControl.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *LeftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *RightMotor = AFMS.getMotor(2);
Adafruit_DCMotor *LiftMotor = AFMS.getMotor(3);

float left_offset = 1.25;
float right_offset = 1;

void MotorSetup() {
  Serial.begin(9600);
  Serial.println("Adafruit Motorshield v2 - Motor setup");

  if (!AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
}

void MotorBack(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LeftMotor->run(FORWARD); //depends on which way the motors are installed
  RightMotor->run(FORWARD);
  LeftMotor->setSpeed(MotorSpeed*left_offset);
  RightMotor->setSpeed(MotorSpeed*right_offset);
  delay(TimeRunning);
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}

void MotorForward(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LeftMotor->run(BACKWARD);
  RightMotor->run(BACKWARD);
  LeftMotor->setSpeed(MotorSpeed*left_offset);
  RightMotor->setSpeed(MotorSpeed*right_offset);
  delay(TimeRunning);
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}

void MotorRight(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LeftMotor->run(BACKWARD);
  RightMotor->run(FORWARD);
  LeftMotor->setSpeed(MotorSpeed*left_offset);
  RightMotor->setSpeed(MotorSpeed*right_offset);
  delay(TimeRunning);
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}

void MotorLeft(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LeftMotor->run(FORWARD);
  RightMotor->run(BACKWARD);
  LeftMotor->setSpeed(MotorSpeed*left_offset);
  RightMotor->setSpeed(MotorSpeed*right_offset);
  delay(TimeRunning);
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}

void MotorOff() {
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}


// code for motion control ----------------------

void MotorAction(char action) {
  // motor action to be called in according to junction type
  int fwd_speed = 150;
  int fwd_time = 200;
  int turn_speed = 150;
  int turn_time = 1200;
  int bwd_speed = 150;
  int bwd_time = 2000;

  switch (action) {
    case 'F':
      MotorForward(fwd_speed, fwd_time);
      break;
    case 'L':
      MotorLeft(turn_speed, turn_time);
      break;
    case 'R':
      MotorRight(turn_speed, turn_time);
      break;
    case 'B':
      MotorBack(bwd_speed, bwd_time);
      break;
    case 'S':
      MotorOff();
      break;
    case 'T':
      MotorLeft(turn_speed, turn_time*2); // turn 180
      break;
  }
}

void LineFollow(int SensorState){
  // different speed & time for each action, to be finetuned
  int straight_speed = 150;
  int straight_time = 100;
  int shift_speed = 100;
  int shift_time = 300;
  int turn_speed = 150;
  int turn_time = 120;

  switch (SensorState) {
    case 1:
    case 7:
    case 4:
    default:
      MotorForward(straight_speed, straight_time);
      break;
    case 2:
      MotorLeft(turn_speed, turn_time);
      MotorForward(shift_speed, shift_time);
      break;
    case 3:
      MotorRight(turn_speed, turn_time);
      MotorForward(shift_speed, shift_time);
      break;
    case 5:
      MotorForward(shift_speed, shift_time);
      MotorRight(turn_speed, turn_time);
      break;
    case 6:
      MotorForward(shift_speed, shift_time);
      MotorLeft(turn_speed, turn_time);
      break;
    case 13:
      // MotorBack(shift_speed, shift_time);
      MotorLeft(turn_speed, turn_time);
      break;
    case 15:
      // MotorBack(shift_speed, shift_time);
      MotorRight(turn_speed, turn_time);
      break;
  } 

}


//motor for lifting--------------------------------

void LiftMotorRaise(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LiftMotor->run(FORWARD);
  LiftMotor->setSpeed(MotorSpeed);
  delay(TimeRunning);
  LiftMotor->run(RELEASE);
}

void LiftMotorLower(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LiftMotor->run(BACKWARD);
  LiftMotor->setSpeed(MotorSpeed);
  delay(TimeRunning);
  LiftMotor->run(RELEASE);
}



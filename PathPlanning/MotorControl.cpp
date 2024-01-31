#include <Adafruit_MotorShield.h>
#include "MotorControl.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *LeftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *RightMotor = AFMS.getMotor(2);
Adafruit_DCMotor *LiftMotor = AFMS.getMotor(3);

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
  LeftMotor->setSpeed(MotorSpeed);
  RightMotor->setSpeed(MotorSpeed);
  delay(TimeRunning);
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}

void MotorForward(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LeftMotor->run(BACKWARD);
  RightMotor->run(BACKWARD);
  LeftMotor->setSpeed(MotorSpeed);
  RightMotor->setSpeed(MotorSpeed);
  delay(TimeRunning);
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}

void MotorRight(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LeftMotor->run(BACKWARD);
  RightMotor->run(FORWARD);
  LeftMotor->setSpeed(MotorSpeed);
  RightMotor->setSpeed(MotorSpeed);
  delay(TimeRunning);
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}

void MotorLeft(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LeftMotor->run(FORWARD);
  RightMotor->run(BACKWARD);
  LeftMotor->setSpeed(MotorSpeed);
  RightMotor->setSpeed(MotorSpeed);
  delay(TimeRunning);
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}

void MotorOff() {
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}

void MotorAction(char action) {
  // motor action to be called in according to junction type
  int fwd_speed = 150;
  int fwd_time = 200;
  int turn_speed = 150;
  int turn_time = 1200;
  int bwd_speed = 100;
  int bwd_time = 200;

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
    case 'S':
      MotorBack(bwd_speed, bwd_time);
      break;
    case 'B':
      MotorOff();
      break;
  }
}

void LineFollow(int SensorState){
  int straight_speed = 100;
  int straight_time = 200;
  int correct_speed = 100;
  int correct_time = 50;
  switch (SensorState) {
    case 1:
    case 7:
    case 0: // ?
      MotorForward(straight_speed, straight_time); // go straight
      break;
    case 5:
    case 2:
    case 13:
      //MotorBack(straight_speed/2, straight_time/2); // reverse a bit
      MotorLeft(correct_speed, correct_time); // correct left
      break;
    case 3:
    case 6:
    case 15:
      //MotorBack(straight_speed/2, straight_time/2); // reverse a bit
      MotorRight(correct_speed, correct_time); // correct right
      break;
    default:
      MotorForward(straight_speed, straight_time);
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



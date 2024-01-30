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

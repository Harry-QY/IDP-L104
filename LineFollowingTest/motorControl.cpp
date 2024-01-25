#include <Adafruit_MotorShield.h>
#include "motorControl.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

void motorSetup() {
  Serial.begin(9600);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
}

void motorBack(int motorSpeed, int timeRunning) { //timeRunning variable in miliseconds
  myMotor1->run(FORWARD); //depends on which way the motors are installed
  myMotor2->run(FORWARD);
  myMotor1->setSpeed(motorSpeed);
  myMotor2->setSpeed(motorSpeed);
  delay(timeRunning);
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
}

void motorForward(int motorSpeed, int timeRunning) { //timeRunning variable in miliseconds
  myMotor1->run(BACKWARD);
  myMotor2->run(BACKWARD);
  myMotor1->setSpeed(motorSpeed);
  myMotor2->setSpeed(motorSpeed);
  delay(timeRunning);
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
}

void motorLeft(int motorSpeed, int timeRunning) { //timeRunning variable in miliseconds
  myMotor1->run(BACKWARD);
  myMotor2->run(FORWARD);
  myMotor1->setSpeed(motorSpeed);
  myMotor2->setSpeed(motorSpeed);
  delay(timeRunning);
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
}

void motorRight(int motorSpeed, int timeRunning) { //timeRunning variable in miliseconds
  myMotor1->run(FORWARD);
  myMotor2->run(BACKWARD);
  myMotor1->setSpeed(motorSpeed);
  myMotor2->setSpeed(motorSpeed);
  delay(timeRunning);
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
}

void motorOff() {
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
}
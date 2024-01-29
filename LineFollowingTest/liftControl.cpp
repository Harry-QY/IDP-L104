#include <Adafruit_MotorShield.h>
#include "liftControl.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *liftMotor = AFMS.getMotor(3);

void liftSetup() {
  Serial.begin(9600);
  Serial.println("Motorshield DC lift Motor test!");

  if (!AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
}

void liftMotorRaise(int motorSpeed, int timeRunning) { //timeRunning variable in miliseconds
  liftMotor->run(FORWARD);
  liftMotor->setSpeed(motorSpeed);
  delay(timeRunning);
  liftMotor->run(RELEASE);
}

void liftMotorLower(int motorSpeed, int timeRunning) { //timeRunning variable in miliseconds
  liftMotor->run(BACKWARD);
  liftMotor->setSpeed(motorSpeed);
  delay(timeRunning);
  liftMotor->run(RELEASE);
}

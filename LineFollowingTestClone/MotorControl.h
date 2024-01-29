#include <Adafruit_MotorShield.h>

#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <arduino.h>

void MotorSetup();
void MotorForward(int MotorSpeed, int TimeRunning);
void MotorBack(int MotorSpeed, int TimeRunning);
void MotorLeft(int MotorSpeed, int TimeRunning);
void MotorRight(int MotorSpeed, int TimeRunning);
void MotorOff();

void LiftMotorLower(int MotorSpeed, int TimeRunning);
void LiftMotorRaise(int MotorSpeed, int TimeRunning);

#endif
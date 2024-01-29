#include <Adafruit_MotorShield.h>

#ifndef DRIVEMOTORCONTROL_H
#define DRIVEMOTORCONTROL_H

#include <arduino.h>

void driveMotorSetup();
void motorForward(int motorSpeed, int timeRunning);
void motorBack(int motorSpeed, int timeRunning);
void motorLeft(int motorSpeed, int timeRunning);
void motorRight(int motorSpeed, int timeRunning);
void motorOff();

#endif
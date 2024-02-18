#include <Adafruit_MotorShield.h>

#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <arduino.h>

void motorSetup();
void motorForward(int motorSpeed, int timeRunning);
void motorBack(int motorSpeed, int timeRunning);
void motorLeft(int motorSpeed, int timeRunning);
void motorRight(int motorSpeed, int timeRunning);
void motorOff();

#endif
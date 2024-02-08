#include <Adafruit_MotorShield.h>
#include <arduino.h>
#include <Ticker.h>

#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

void MotorAction(char action);
void LineFollow(int SensorState);

void LiftMotorLower(int MotorSpeed, int TimeRunning);
void LiftMotorRaise(int MotorSpeed, int TimeRunning);

void MotorSetup();
void MotorForward(int MotorSpeed, int TimeRunning);
void MotorBack(int MotorSpeed, int TimeRunning);
void MotorLeft(int MotorSpeed, int TimeRunning);
void MotorRight(int MotorSpeed, int TimeRunning);
void MotorOff();

#endif
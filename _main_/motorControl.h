#include <Adafruit_MotorShield.h>
#include <arduino.h>
#include <Ticker.h>
#include "Pathfinding.h"

#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

extern float throttle;

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

void LiftMotorLower(int MotorSpeed, int TimeRunning);
void LiftMotorRaise(int MotorSpeed, int TimeRunning);
void ServoTighten(int StartAngle, int FinalAngle);
void ServoLoosen(int StartAngle, int FinalAngle);
void ClampAndLift(int ClampAngle = 60, int LiftTime = 2000);
void DescendAndRelease(int ClampAngle = 40, int LiftTime = 2000);

extern Ticker ServoGripTicker; 

void ServoGrip(int StartAngle);
void onServoGrip();
void offServoGrip();


#endif
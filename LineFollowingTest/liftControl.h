#include <Adafruit_MotorShield.h>

#ifndef LIFTCONTROL_H
#define LIFTCONTROL_H

#include <arduino.h>

void liftSetup();
void liftMotorRaise(int motorSpeed, int timeRunning);
void liftMotorLower(int motorSpeed, int timeRunning);


#endif
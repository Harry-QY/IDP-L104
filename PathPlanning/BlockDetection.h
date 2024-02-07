#ifndef BLOCKDETECTION_H
#define BLOCKDETECTION_H

#include <arduino.h>
#include "Wire.h"
#include "DFRobot_VL53L0X.h"

extern DFRobot_VL53L0X sensor;

void DetectionSensorsSetup();
int mostFrequent(int* array);
int BlockIdentification();

#endif
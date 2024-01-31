#ifndef BLOCKDETECTION_H
#define BLOCKDETECTION_H

#include <arduino.h>


void DetectionSensorsSetup();
int mostFrequent(int* SomeArray);
int num_iterations = 20; //#### change each time you change time_delay >> 1000/time_delay


#endif
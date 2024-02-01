#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <arduino.h>
#include "MotorControl.h"
#include "LineSensorCombinations.h"

void FollowPath(int* current_path, char* current_actions, int path_size);

#endif
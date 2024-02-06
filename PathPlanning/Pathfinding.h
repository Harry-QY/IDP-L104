#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <arduino.h>
#include "MotorControl.h"
#include "LineSensorCombinations.h"
#include "DFRobot_VL53L0X.h"
#include "BlockDetection.h"
#include <Ticker.h>

void FollowPath(int* current_path, char* current_actions, int path_size);
void BlockFinding();
void PlatformFinding();

#endif
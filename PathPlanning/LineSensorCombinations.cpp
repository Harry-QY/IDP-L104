#include "LineSensorCombinations.h"
#include "MotorControl.h"

int lineSensorStates(int lsv, int rsv, int fsv, int bsv) {
  String lineSensorStatesMessage;
  int SensorState;
  if (lsv == 0 and rsv == 0 and fsv == 0 and bsv == 0) {
    // State 0 = 0000: start box / lost track -> need a correction loop
    // industrial area behavior tbc in here
    SensorState = 0;
  }
  if (lsv == 0 and rsv == 0 and fsv == 1 and bsv == 0) {
    // State 1 = 0010: end of line (reverse), inverse T (missed)
    // move forward to confirm?
    SensorState = 1;
  }
  if (lsv == 1 and rsv == 0 and fsv == 0 and bsv == 0) {
    // State 2 = 1000: right side of the line
    // left then forward
    SensorState = 2;
  }
  if (lsv == 0 and rsv == 1 and fsv == 0 and bsv == 0) {
    // State 3 = 1000: right side of the line
    // right then forward
    SensorState = 3;
  }
  if (lsv == 0 and rsv == 0 and fsv == 0 and bsv == 1) {
    // State 4 = 0001: end of line / platform
    // stop
    SensorState = 4;
  }
  if (lsv == 1 and rsv == 0 and fsv == 1 and bsv == 0) {
    // State 5 = 1010: right side of the line
    // forward then right
    SensorState = 5;
  }
  if (lsv == 0 and rsv == 1 and fsv == 1 and bsv == 0) {
    // State 6 = 0110: left side of line
    // forward then left
    SensorState = 6;
  }
  if (lsv == 0 and rsv == 0 and fsv == 1 and bsv == 1) {
    // State 7 = 0011: ideal go straight
    // forward
    SensorState = 7;
  }
  if (lsv == 1 and rsv == 1 and fsv == 1 and bsv == 0) {
    // State 8 = 1110: inverse T junction
    // action based on planned path
    SensorState = 8;
  }
  if (lsv == 1 and rsv == 0 and fsv == 1 and bsv == 1) {
    // State 9 = 1011: ideal left hand junction
    // action based on planned path
    SensorState = 9;
  }
  if (lsv == 0 and rsv == 1 and fsv == 1 and bsv == 1) {
    // State 10 = 0111: ideal  right hand junction
    // action based on planned path
    SensorState = 10;
  }
  if (lsv == 1 and rsv == 1 and fsv == 1 and bsv == 1) {
    // State 11 = 1111: shouldn't be possible
    SensorState = 11;
  }
  if (lsv == 1 and rsv == 1 and fsv == 0 and bsv == 0) {
    // State 12 = 1100: perpendicular to line -> turn 90 degree
    // need to consider direction heading
    SensorState = 12;
  }
  if (lsv == 1 and rsv == 0 and fsv == 0 and bsv == 1) { 
    // State 13 = 1001: right side of line
    // reverse then left 
    SensorState = 13;
  }
  if (lsv == 1 and rsv == 1 and fsv == 0 and bsv == 1) {
    // State 14 = 1101: T junction
    // actions based on planned path
    SensorState = 14;
  }
  if (lsv == 0 and rsv == 1 and fsv == 0 and bsv == 1) {
    // State 15 = left side of line
    // reverse then right
    SensorState = 15;
  }
    //Serial.println(lineSensorStatesMessage);
    return SensorState;
}
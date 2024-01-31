#include "LineSensorCombinations.h"
#include "MotorControl.h"

int lineSensorStates(int lsv, int rsv, int fsv, int bsv) {
  String lineSensorStatesMessage;
  int SensorState;
  if (lsv == 0 and rsv == 0 and fsv == 0 and bsv == 0) {
    //lineSensorStatesMessage = "0000: start box?"; //industrial area behavior tbc in here
    SensorState = 0;
    //motorForward(fwd_speed, fwd_time);
  }
  if (lsv == 0 and rsv == 0 and fsv == 1 and bsv == 0) {
    //lineSensorStatesMessage = "0010: straight";
    SensorState = 1;
    //motorForward(fwd_speed, fwd_time);
  }
  if (lsv == 1 and rsv == 0 and fsv == 0 and bsv == 0) {
    //lineSensorStatesMessage = "1000: left turn";
    SensorState = 2;
    //motorLeft(turn_speed, turn_time);
  }
  if (lsv == 0 and rsv == 1 and fsv == 0 and bsv == 0) {
    //lineSensorStatesMessage = "0100: right turn";
    SensorState = 3;
    //motorRight(turn_speed, turn_time);
  }
  if (lsv == 0 and rsv == 0 and fsv == 0 and bsv == 1) {
    //lineSensorStatesMessage = "0001: end of line/platform";
    SensorState = 4;
    //motorBack(fwd_speed, fwd_time);
  }
  if (lsv == 1 and rsv == 0 and fsv == 1 and bsv == 0) {
    //lineSensorStatesMessage = "1010: correct left (hopefully no junction)"; //assuming back sensor is far back enough
    SensorState = 5;
    //motorLeft(turn_speed, turn_time);
  }
  if (lsv == 0 and rsv == 1 and fsv == 1 and bsv == 0) {
    //lineSensorStatesMessage = "0110: correct right (hopefully no junction)";
    SensorState = 6;
    //motorRight(turn_speed, turn_time);
  }
  if (lsv == 0 and rsv == 0 and fsv == 1 and bsv == 1) {
    //lineSensorStatesMessage = "0011: Ideal go straight case";
    SensorState = 7;
    //motorForward(fwd_speed, fwd_time);
  }
  if (lsv == 1 and rsv == 1 and fsv == 1 and bsv == 0) {
    //lineSensorStatesMessage = "1110: Inverse T junction";
    SensorState = 8;
    //motorForward(fwd_speed, fwd_time);
  }
  if (lsv == 1 and rsv == 0 and fsv == 1 and bsv == 1) {
    //lineSensorStatesMessage = "1011: Ideally left hand junction ";
    SensorState = 9;
    //motorLeft(turn_speed, turn_time);
  }
  if (lsv == 0 and rsv == 1 and fsv == 1 and bsv == 1) {
    //lineSensorStatesMessage = "0111: Ideally right hand junction ";
    SensorState = 10;
    //motorRight(turn_speed, turn_time);
  }
  if (lsv == 1 and rsv == 1 and fsv == 1 and bsv == 1) {
    //lineSensorStatesMessage = "1111: Shouldn't be possible";
    SensorState = 11;
    //motorForward(fwd_speed, fwd_time);
  }
  if (lsv == 1 and rsv == 1 and fsv == 0 and bsv == 0) {
    //lineSensorStatesMessage = "1100: Unsure, turn 90 degree?";
    SensorState = 12;
    //motorLeft(turn_speed, turn_time);
  }
  if (lsv == 1 and rsv == 0 and fsv == 0 and bsv == 1) { 
    lineSensorStatesMessage = "1001: correct left"; //assuming front sensor is far forward enough
    SensorState = 13;
    //motorLeft(turn_speed, turn_time);
  }
  if (lsv == 1 and rsv == 1 and fsv == 0 and bsv == 1) {
    lineSensorStatesMessage = "1101: T Junction, pathfinding based decision";
    SensorState = 14;
    //motorLeft(turn_speed, turn_time);
  }
  if (lsv == 0 and rsv == 1 and fsv == 0 and bsv == 1) {
    //lineSensorStatesMessage = "0101: correct right"; //assuming front sensor is far forward enough
    SensorState = 15;
    //motorRight(turn_speed, turn_time);
  }
    //Serial.println(lineSensorStatesMessage);
    return SensorState;
}
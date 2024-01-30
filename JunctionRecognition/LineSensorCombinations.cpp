#include "LineSensorCombinations.h"

string lineSensorStates(lsv, rsv, fsv, bsv, fwd_speed, fwd_time, turn_speed, turn_time) {
  string lineSensorStatesMessage;
  if (lsv == 0 and rsv == 0 and fsv == 0 and bsv == 0) {
    lineSensorStatesMessage = "0000: start box?"; //industrial area behavior tbc in here
    motorForward(fwd_speed, fwd_time);
  }
  if (lsv == 0 and rsv == 0 and fsv == 1 and bsv == 0) {
    lineSensorStatesMessage = "0010: straight";
    motorForward(fwd_speed, fwd_time);
  }
  if (lsv == 1 and rsv == 0 and fsv == 0 and bsv == 0) {
    lineSensorStatesMessage = "1000: left turn";
    motorLeft(turn_speed, turn_time);
  }
  if (lsv == 0 and rsv == 1 and fsv == 0 and bsv == 0) {
    lineSensorStatesMessage = "0100: right";
    motorRight(turn_speed, turn_time);
  }
  if (lsv == 0 and rsv == 0 and fsv == 0 and bsv == 1) {
    lineSensorStatesMessage = "0001: unsure but reverses maybe";
    motorBack(fwd_speed, fwd_time);
  }
  if (lsv == 1 and rsv == 0 and fsv == 1 and bsv == 0) {
    lineSensorStatesMessage = "1010: correct left (hopefully no junction)"; //assuming back sensor is far back enough
    motorLeft(turn_speed, turn_time);
  }
  if (lsv == 0 and rsv == 1 and fsv == 1 and bsv == 0) {
    lineSensorStatesMessage = "0110: correct right (hopefully no junction)";
    motorRight(turn_speed, turn_time);
  }
  if (lsv == 0 and rsv == 0 and fsv == 1 and bsv == 1) {
    lineSensorStatesMessage = "0011: Ideal go straight case";
    motorForward(fwd_speed, fwd_time);
  }
  if (lsv == 1 and rsv == 1 and fsv == 1 and bsv == 0) {
    lineSensorStatesMessage = "1110: Aprroaching T from side with no path - go forward";
    motorForward(fwd_speed, fwd_time);
  }
  if (lsv == 1 and rsv == 0 and fsv == 1 and bsv == 1) {
    lineSensorStatesMessage = "1011: Ideally left hand junction ";
    motorLeft(turn_speed, turn_time);
  }
  if (lsv == 0 and rsv == 1 and fsv == 1 and bsv == 1) {
    lineSensorStatesMessage = "0111: Ideally right hand junction ";
    motorRight(turn_speed, turn_time);
  }
  if (lsv == 1 and rsv == 1 and fsv == 1 and bsv == 1) {
    lineSensorStatesMessage = "1111: Shouldn't be possible";
    motorForward(fwd_speed, fwd_time);
  }
  if (lsv == 1 and rsv == 1 and fsv == 0 and bsv == 0) {
    lineSensorStatesMessage = "1100: Unsure";
    motorLeft(turn_speed, turn_time);
  }
  if (lsv == 1 and rsv == 0 and fsv == 0 and bsv == 1) {
    lineSensorStatesMessage = "1001: ";
    motorLeft(turn_speed, turn_time);
  }
  if (lsv == 1 and rsv == 1 and fsv == 0 and bsv == 1) {
    lineSensorStatesMessage = "1101: T Junction, pathfinding based decision";
    motorLeft(turn_speed, turn_time);
  }
  if (lsv == 0 and rsv == 1 and fsv == 0 and bsv == 1) {
    lineSensorStatesMessage = "0101: ";
    motorRight(turn_speed, turn_time);
  }
    Serial.println(lineSensorStatesMessage);
}
#include <Adafruit_MotorShield.h>
#include "MotorControl.h"
#include "LEDControl.h"
#include <Servo.h>
#define blueLED 4 // blue LED

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *LeftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *RightMotor = AFMS.getMotor(2);
Adafruit_DCMotor *LiftMotor = AFMS.getMotor(3);

Servo myservo; // create servo object to control a servo
int pos = 0; // variable to store the servo position

float left_offset = 1.05; //Sometimes the drive motors don't spin at the same rate. offsets used to calibrate this.
float right_offset = 1;
float throttle = 1;


void MotorSetup() { //Function called in setup(){ function in .ino file.
  myservo.attach(2); // attaches the servo on pin 8 to the servo object
  Serial.begin(9600);
  if (!AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);}
  Serial.println("Motor Shield found.");
}

void MotorAction(char action) {
  // motor action to be called in according to junction type
  int fwd_speed = 170;
  int fwd_time = 250;
  int turn_speed = 130;
  int turn_time = 1400;
  int bwd_speed = 170;
  int bwd_time = 250;

  switch (action) {
    case 'F':
      MotorForward(fwd_speed, fwd_time);
      break;
    case 'L':
      MotorLeft(turn_speed, turn_time);
      MotorForward(fwd_speed, fwd_time/1.5);
      break;
    case 'l':
      MotorBack(bwd_speed, bwd_time);
      MotorLeft(turn_speed, turn_time);
      MotorForward(fwd_speed, fwd_time/1.5);
      break;
    case 'R':
      MotorRight(turn_speed, turn_time);
      MotorForward(fwd_speed, fwd_time/1.5);
      break;
    case 'r':
      MotorBack(bwd_speed, bwd_time);
      MotorRight(turn_speed, turn_time);
      MotorForward(fwd_speed, fwd_time/1.5);
      break;
    case 'B':
      MotorBack(bwd_speed, bwd_time);
      break;
    case 'S':
      MotorOff();
      break;
    case 'T':
      Serial.println("should rev then 180");
      MotorBack(bwd_speed, bwd_time/2);
      MotorLeft(turn_speed, turn_time*2.7); // turn 180
      MotorBack(bwd_speed, bwd_time);
      break;
  }
}

void LineFollow(int SensorState){
  // different speed & time for each action, to be finetuned. This is different to speeds used after detecting a junction.
  int straight_speed = 150;
  int straight_time = 90;
  int shift_speed = 150;
  int shift_time = 100;
  int turn_speed = 120;
  int turn_time = 90;

  switch (SensorState) { 
    case 1:
    case 7:
    case 4:
    default:
      MotorForward(straight_speed*throttle, straight_time);
      odometry += straight_speed*throttle*straight_time;
      break;
    case 2:
      MotorLeft(turn_speed, turn_time);
      MotorForward(shift_speed*throttle, shift_time);
      odometry += shift_speed*throttle*shift_time;
      break;
    case 3:
      MotorRight(turn_speed, turn_time);
      MotorForward(shift_speed*throttle, shift_time);
      odometry += shift_speed*throttle*shift_time;
      break;
    case 5:
      MotorForward(shift_speed*throttle, shift_time);
      MotorRight(turn_speed, turn_time);
      odometry += shift_speed*throttle*shift_time;
      break;
    case 6:
      MotorForward(shift_speed*throttle, shift_time);
      MotorLeft(turn_speed, turn_time);
      odometry += shift_speed*throttle*shift_time;
      break;
    case 13:
      // MotorBack(shift_speed, shift_time);
      MotorLeft(turn_speed, turn_time);
      break;
    case 15:
      // MotorBack(shift_speed, shift_time);
      MotorRight(turn_speed, turn_time);
      break;
  } 
}

//motor for lifting and functions--------------------------------

void LiftMotorLower(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LiftMotor->run(FORWARD);
  Serial.println("Run forward");
  LiftMotor->setSpeed(MotorSpeed);
  delay(TimeRunning);
  LiftMotor->run(RELEASE);
}

void LiftMotorRaise(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LiftMotor->run(BACKWARD);
  Serial.println("Run backward");
  LiftMotor->setSpeed(MotorSpeed);
  delay(TimeRunning);
  LiftMotor->run(RELEASE);
}

void ServoTighten(int StartAngle, int FinalAngle) {
 for (pos = StartAngle; pos <= FinalAngle; pos += 1) { // goes from 0 degrees to 180 degrees
  myservo.write(pos); // tell servo to go to position in variable 'pos'
  delay(15); // waits 15 ms for the servo to reach the position
 }
  Serial.print("Tightened by ");
  Serial.print(FinalAngle);
  Serial.println(" degrees.");
}

void ServoLoosen(int StartAngle, int FinalAngle) {
  for (pos = StartAngle; pos >= FinalAngle; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos); // tell servo to go to position in variable 'pos'
    delay(15); // waits 15 ms for the servo to reach the position
  }
  Serial.print("Returned back from ");
  Serial.print(StartAngle);
  Serial.println(" degrees.");
}

void ClampAndLift(int ClampAngle = 60, int LiftTime = 2000) {
  ServoTighten(0, ClampAngle);
  LiftMotorRaise(100, LiftTime);
}

void DescendAndRelease(int ClampAngle = 40, int LiftTime = 2000){ //LiftMotorCorrectionFactor is a percentage
  LiftMotorLower(100, LiftTime);
  ServoLoosen(ClampAngle, 0);
}
//general motor running--------------------------------------------------------------------------

void MotorBack(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LeftMotor->run(FORWARD); //depends on which way the motors are installed
  RightMotor->run(FORWARD);
  LeftMotor->setSpeed(MotorSpeed*left_offset);
  RightMotor->setSpeed(MotorSpeed*right_offset);
  delay(TimeRunning);
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}

void MotorForward(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LeftMotor->run(BACKWARD);
  RightMotor->run(BACKWARD);
  LeftMotor->setSpeed(MotorSpeed*left_offset);
  RightMotor->setSpeed(MotorSpeed*right_offset);
  delay(TimeRunning);
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}

void MotorRight(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LeftMotor->run(BACKWARD);
  RightMotor->run(FORWARD);
  LeftMotor->setSpeed(MotorSpeed*left_offset);
  RightMotor->setSpeed(MotorSpeed*right_offset);
  delay(TimeRunning/4);
  blueLEDticker.update();
  delay(TimeRunning/4);
  blueLEDticker.update();
  delay(TimeRunning/4);
  blueLEDticker.update();
  delay(TimeRunning/4);
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}

void MotorLeft(int MotorSpeed, int TimeRunning) { //timeRunning variable in miliseconds
  LeftMotor->run(FORWARD);
  RightMotor->run(BACKWARD);
  LeftMotor->setSpeed(MotorSpeed*left_offset);
  RightMotor->setSpeed(MotorSpeed*right_offset);
  delay(TimeRunning/4);
  blueLEDticker.update();
  delay(TimeRunning/4);
  blueLEDticker.update();
  delay(TimeRunning/4);
  blueLEDticker.update();
  delay(TimeRunning/4);
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}

void MotorOff() {
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
}

//Servomotor ---------------------------------------------------------------------------------------------------------------------------







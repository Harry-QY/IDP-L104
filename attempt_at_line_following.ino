#include <Adafruit_MotorShield.h> //header file for protecting motors

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

int ledPin = 2;    // choose the pin for the LED
int inputPin = 3;  // Connect sensor to input pin 3

void buttonSetup() {
  pinMode(ledPin, OUTPUT);   // declare LED as output
  pinMode(inputPin, INPUT);  // declare pushbutton as input
}

void motorSetup() {
  Serial.begin(9600);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
}

void motorForward(int motorSpeed, int timeRunning) { //timeRunning variable in miliseconds
  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  myMotor1->setSpeed(motorSpeed);
  myMotor2->setSpeed(motorSpeed);
  delay(timeRunning);
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
}

void motorBack(int motorSpeed, int timeRunning) { //timeRunning variable in miliseconds
  myMotor1->run(BACKWARD);
  myMotor2->run(BACKWARD);
  myMotor1->setSpeed(motorSpeed);
  myMotor2->setSpeed(motorSpeed);
  delay(timeRunning);
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
}

void motorLeft(int motorSpeed, int timeRunning) { //timeRunning variable in miliseconds
  myMotor1->run(BACKWARD);
  myMotor2->run(FORWARD);
  myMotor1->setSpeed(motorSpeed);
  myMotor2->setSpeed(motorSpeed);
  delay(timeRunning);
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
}

void motorRight(int motorSpeed, int timeRunning) { //timeRunning variable in miliseconds
  myMotor1->run(FORWARD);
  myMotor2->run(BACKWARD);
  myMotor1->setSpeed(motorSpeed);
  myMotor2->setSpeed(motorSpeed);
  delay(timeRunning);
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
}

void motorOff() {
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
}

void setup() {
  buttonSetup();
  motorSetup();
}

void loop() {
  int val = digitalRead(inputPin);
  if (val == HIGH) {
    motorForward(100, 5000);
    motorLeft(250, 5000);
    motorBack(150, 10000);
    motorRight(50, 25000);
  }
}
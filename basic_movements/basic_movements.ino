#include <Adafruit_MotorShield.h> //header file for protecting motors
#include "motorControl.h"

int ledPin = 2;    // choose the pin for the LED
int inputPin = 3;  // Connect sensor to input pin 3

void buttonSetup() {
  pinMode(ledPin, OUTPUT);   // declare LED as output
  pinMode(inputPin, INPUT);  // declare pushbutton as input
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
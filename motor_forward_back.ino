#include <Adafruit_MotorShield.h>

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

  myMotor1->setSpeed(150);
  myMotor1->run(FORWARD);
  myMotor1->run(RELEASE);
  myMotor2->setSpeed(150);
  myMotor2->run(FORWARD);
  myMotor2->run(RELEASE);
}

void motorSequence() {
  Serial.print("tick");

  myMotor1->run(FORWARD);
  myMotor2->run(FORWARD);
  for (uint8_t i = 0; i < 255; i++) {
    myMotor1->setSpeed(i);
    myMotor2->setSpeed(i);
    delay(10);
  }
  for (uint8_t i = 255; i != 0; i--) {
    myMotor1->setSpeed(i);
    myMotor2->setSpeed(i);
    delay(10);
  }

  Serial.print("tock");

  myMotor1->run(BACKWARD);
  myMotor2->run(BACKWARD);
  for (uint8_t i = 0; i < 255; i++) {
    myMotor1->setSpeed(i);
    myMotor2->setSpeed(i);
    delay(10);
  }
  for (uint8_t i = 255; i != 0; i--) {
    myMotor1->setSpeed(i);
    myMotor2->setSpeed(i);
    delay(10);
  }

  Serial.print("tech");
  myMotor1->run(RELEASE);
  myMotor2->run(RELEASE);
  delay(1000);
}

void setup() {
  buttonSetup();
  motorSetup();
}

void loop() {
  int val = digitalRead(inputPin);
  if (val == HIGH) {
    motorSequence();
  }
}



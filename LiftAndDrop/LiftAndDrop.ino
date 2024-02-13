#include <Servo.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *LiftMotor = AFMS.getMotor(3);

Servo myservo; // create servo object to control a servo
int pos = 0; // variable to store the servo position
void setup() {
  myservo.attach(2); // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  if (!AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);}
  Serial.println("Motor Shield found.");
}

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

int start = 1;
void loop() {
  while (start == 1) {
  ClampAndLift();
  DescendAndRelease();
  start = 0;
  }
}

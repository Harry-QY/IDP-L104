#include <Adafruit_MotorShield.h> //header file for protecting motors
#include "MotorControl.h"
#include "LineSensorCombinations.h"

#define ls 6 // left sensor
#define rs 7 // right sensor
#define fs 8 // front sensor
#define bs 9 // back sensor
#define btn 3 // btn
int lsv, rsv, fsv, bsv;

int start = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(btn, INPUT);  // declare pushbutton as input
  MotorSetup();
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ls, INPUT);
  pinMode(rs, INPUT);
  pinMode(fs, INPUT);
  pinMode(bs, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (digitalRead(btn) == 1) {
    start = !start;
    delay(500);
    Serial.print("Button pressed, robot is in state: ");
    Serial.println(start);}

    if (start == 1) {
    lsv = digitalRead(ls);
    rsv = digitalRead(rs);
    fsv = digitalRead(fs);
    bsv = digitalRead(bs);
    int SensorState = lineSensorStates(lsv, rsv, fsv, bsv);
    Serial.print("Current state: ");
    Serial.println(SensorState);
    LineFollow(SensorState);
  }

}

#include <Adafruit_MotorShield.h> //header file for protecting motors
#include "motorControl.h"
#include "sensorControl.h"
#include "LineSensorCombinations.h"

#define ls 6 // left sensor
#define rs 7 // right sensor
#define fs 8 // front sensor
#define bs 9 // back sensor

int lsv, rsv, fsv, bsv;
int btn = 3; //sets button

int fwd_speed = 230;
int fwd_time = 100;
int turn_speed = 100;
int turn_time = 100;

int start = 0;
int mode = 0;

void setup() {
  pinMode(btn, INPUT);  // declare pushbutton as input
  motorSetup();
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ls, INPUT);
  pinMode(rs, INPUT);
  pinMode(fs, INPUT);
  pinMode(bs, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // 0 for going straight, L for left junction, R for right junction, F for front junction and B for back junction
  if (digitalRead(btn) == 1) {
    start = !start;
    delay(500);
    Serial.print("Button pressed, robot is in state: ");
    Serial.println(start);
  }

  if (start == 1) {
    // put your main code here, to run repeatedly:
    lsv = digitalRead(ls);
    rsv = digitalRead(rs);
    fsv = digitalRead(fs);
    bsv = digitalRead(bs);

    lineSensorStates(lsv, rsv, fsv, bsv, fwd_speed, fwd_time, turn_speed, turn_time);
    
  }

}

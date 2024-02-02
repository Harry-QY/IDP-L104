#include <arduino.h>
#include "Ticker.h"

#define blueLED 7

bool ledState;

void flipLED() {
  ledState = !ledState;
}

Ticker timer2(flipLED, 1000, 0, MILLIS);

void setup() {
  //pinMode(LED_BUILTIN, OUTPUT); unsure what this does
  Serial.begin(9600);
  delay(2000);
  timer2.start();
  }

void loop() {
  timer2.update();
}



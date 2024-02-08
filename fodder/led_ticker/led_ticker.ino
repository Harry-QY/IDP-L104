#include <arduino.h>
#include "Ticker.h"

#define blueLED 7
int btn = 3; //sets button

bool blueLedState = 0;
bool LED_state = 0;
bool start_ticker = 0;
bool stop_ticker = 1;

void flipLED() {
  blueLedState = !blueLedState;
  digitalWrite(blueLED, blueLedState);
  Serial.println("LED flipped!");
}

Ticker blueLEDticker(flipLED, 500, 0, MILLIS);

void setup() {
  pinMode(blueLED, OUTPUT);
  pinMode(btn, INPUT);
  Serial.begin(9600);
  delay(2000);
  blueLEDticker.start();
  Serial.println("Finished setup");
  }


void loop() {
  if (digitalRead(btn) == 1) {
    LED_state = !LED_state; //Indicates if LED sequence should be on or off, off = 0, on = 1.
    if (LED_state == 0) {
      stop_ticker = 1; //If want to turn off LED sequence, stop_ticker set to 1. Reset to 0 after running blueLEDticker.stop() once.
    }
    if (LED_state == 1) {
      start_ticker = 1; ////If want to turn on LED sequence, start_ticker set to 1. Reset to 0 after running blueLEDticker.start() once.
    }
    Serial.println("Button pressed!");
    delay(500);
  }

  if (start_ticker == 1) {
    blueLEDticker.start();
    Serial.println("LED seq should have started");
    start_ticker = 0;
  }

  if (stop_ticker == 1) {
    blueLEDticker.stop();
    digitalWrite(blueLED, 0); //Make sure blueLEDticker doesnt end with blueLED still on
    Serial.println("LED seq should have stopped");
    stop_ticker = 0;
  }

  blueLEDticker.update(); //required to flip LED. Works different to the .detach() function we used in for coursework since those only work with ARM stuff.
}


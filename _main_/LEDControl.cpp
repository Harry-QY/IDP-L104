#include "LEDControl.h"
#include "Ticker.h"

#define blueLED 4 // blue LED

Ticker blueLEDticker(flipblueLED, 250, 0, MILLIS); //Ticker used with flipblueLED function. This is activated using "onBlueLED" function

bool blueLedState = 0; //Boolean, is LED on (1) or off (0).
bool redLedState = 0; // ""
bool greenLedState = 0; // ""
bool start_ticker = 0; //Default 0 even if ticker is attached, if ticker is not but needs to be attached this is set to 1
bool stop_ticker = 1; //Default 0 even if ticker is off, if ticker is on but needs to be detatched this is set to 1


int flipblueLED() {
  blueLedState = !blueLedState;
  digitalWrite(blueLED, blueLedState);
}


void flipblueLEDsequence(bool LED_state, bool start_ticker, bool stop_ticker) { //This code was used with the button, mostly replaced with more simple onBlueLEDsequence below.
    LED_state = !LED_state; //Indicates if LED sequence should be on or off, off = 0, on = 1.
    
    if (LED_state == 0) {
      stop_ticker = 1; //If want to turn off LED sequence, stop_ticker set to 1. Reset to 0 after running blueLEDticker.stop() once.
    }
    if (LED_state == 1) {
      start_ticker = 1; ////If want to turn on LED sequence, start_ticker set to 1. Reset to 0 after running blueLEDticker.start() once.
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
}

void onblueLEDsequence() {
  blueLEDticker.start();
  Serial.println("LED seq should have started");
}

void offblueLEDsequence() {
  blueLEDticker.stop();
  digitalWrite(blueLED, 0);
  Serial.println("LED seq should have stopped");
}
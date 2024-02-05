#include "LEDControl.h"
#include "Ticker.h"

#define blueLED 7 // blue LED

Ticker blueLEDticker(flipLED, 500, 0, MILLIS);

bool blueLedState = 0;

void flipblueLED(blueLED) {
  blueLedState = !blueLedState;
  digitalWrite(blueLED, blueLedState);
  Serial.println("LED flipped!");
}

void flipblueLEDsequence(bool LED_state, bool start_ticker, bool stop_ticker) {
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


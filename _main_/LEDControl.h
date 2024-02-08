#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <arduino.h>
#include <Ticker.h>

extern Ticker blueLEDticker;

int flipblueLED();
void flipblueLEDsequence();
void onblueLEDsequence();
void offblueLEDsequence();

#endif
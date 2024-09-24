#ifndef test
#define test
#include "Setup.h"
#endif

#define BLINK  1
#define ON 2
#define OFF 3

void IRAM_ATTR onTimer();
void SetTimer();
void LedOn();
void LedOff();
void LedBlink();
void UpdateLed();


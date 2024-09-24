#include "ButtonActions.h"

volatile byte blinkState;
byte ledState;
hw_timer_t * timer = NULL;

void IRAM_ATTR onTimer()
{
    blinkState = !blinkState;
}

void SetTimer()
{
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 1000000, true);
    timerAlarmEnable(timer);
    ledState = OFF;
    blinkState = false;
}



void LedBlink()
{
    ledState = BLINK;
}
void LedOff()
{
    ledState = OFF;
}
void LedOn()
{
    ledState = ON;
}

void UpdateLed()
{
    
    switch (ledState)
    {
    case ON:
        digitalWrite(LED_PIN,HIGH);
        break;
    case OFF:
        digitalWrite(LED_PIN,LOW);
        break;
    case BLINK:
        digitalWrite(LED_PIN,blinkState);
        break;
}


       
}

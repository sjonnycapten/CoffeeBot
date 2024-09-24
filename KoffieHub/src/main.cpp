

#include "Setup.h"
#include <Arduino.h>


void setup()
{
  Serial.begin(115200);

  SetupDisplay();
  pinMode(BUTTON_PIN, INPUT);
  pinMode(WIFI_LED_PIN,OUTPUT);
  digitalWrite(WIFI_LED_PIN,HIGH);
  // Setup pushbutton Bouncer object
  bouncer.attach(BUTTON_PIN);
  bouncer.interval(5);

  
#ifdef MQTT
  SetupWiFi();
  SetupMQTT();
#endif
}

void loop()
{
  bouncer.update();
#ifdef MQTT
  client.loop();
#endif

  if (bouncer.rose())
  {
    display.clearDisplay();
    Serial.println("button pressed");
    ChangeCoffeeState();
  }
}
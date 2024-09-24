#include "Setup.h"
//volatile byte state = LOW;



void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  digitalWrite(LED_PIN, LOW);
  pinMode(WIFI_LED_PIN, OUTPUT);
  digitalWrite(WIFI_LED_PIN,HIGH);
  // Setup pushbutton Bouncer object
  bouncer.attach(BUTTON_PIN);
  bouncer.interval(5);

  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(SSID);

  
  SetupWiFi();

 // SetupMQTT();
  SetTimer();
}

void loop()
{

   // Update button state
    //bouncer.update();
    client.loop();
    //UpdateLed();
    //CheckWiFiConnection();

    /*switch (coffeeState)
    {
    case STATE_COFFEE_MAKING:
      SendMessageOnButtonPress(bouncer);
      LedBlink();
      break;
    case STATE_COFFEE_NOTREADY:
      LedOff();
      break;
    case STATE_COFFEE_REQUEST_RECEIVED:
      LedOn();
      break;
    default:
      break;
    }*/
    
    

} 
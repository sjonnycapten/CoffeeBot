#include <Arduino.h>
#include <stdint.h>
#include <stdint.h>
#include <Bounce2.h>      // Used for "debouncing" the pushbutton
#include <WiFi.h>         // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
#include "ButtonActions.h"
#include "CommunicationTable.h"
#define LED_PIN 4
#define BUTTON_PIN 13
#define WIFI_LED_PIN 2

#define SSID "SSID"
#define WIFI_PASSWORD "SSID"


#define MQTT_SERVER "192.168.178.100"
#define MQTT_TOPPIC "buttons"
#define MQTT_USERNAME "sjonnycapten"
#define MQTT_PASSWORD "PASSWORD"
#define CLIENT_ID JAN
#define CLIENT_ID_MASK DEST_JAN
#define CLIENT_ID_COMPARE CLIENT_ID_MASK >> 4
#define TOPPIC_HUB "hub"
#define TOPPIC_BUTTONS "buttons"


#define STATE_COFFEE_NOTREADY 0
#define STATE_COFFEE_MAKING 1
#define STATE_COFFEE_REQUEST_RECEIVED 2


extern byte coffeeState;
extern Bounce bouncer;
extern PubSubClient client;

void SetupMQTT();
void callback(char *topic, byte *payload, unsigned int length);
void callbackNew(char *topic, byte *payload, unsigned int length);
void SendMessageOnButtonPress(Bounce bouncer);
void Test2(Bounce bouncer);
char * PrepareData(char *data);
void HandlePayload(uint8_t sender,uint8_t command);
void sendData(uint8_t command,char * toppic);
void CheckWiFiConnection();
void SetupWiFi();
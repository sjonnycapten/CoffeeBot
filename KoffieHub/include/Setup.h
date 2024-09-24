#define MQTT
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#include <Arduino.h>
#include <Bounce2.h>      // Used for "debouncing" the pushbutton
#include <WiFi.h>         // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "CommunicationTable.h"
#include <esp_wifi.h>
#ifndef comm
#define comm
#include "Communication.h"
#endif



#define BUTTON_PIN 13
#define WIFI_LED_PIN 2

#define SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

#define MQTT_SERVER "192.168.178.100"
#define MQTT_TOPPIC "buttons"
#define MQTT_USERNAME "USERNAME"
#define MQTT_PASSWORD "PASSWORD"
#define CLIENT_ID HUB
#define TOPPIC_HUB "hub"
#define TOPPIC_BUTTONS "buttons"

#define STATE_COFFEE_NOTREADY 0
#define STATE_COFFEE_MAKING 1
#define STATE_COFFEE_REQUEST_RECEIVED 2

void SetupMQTT();
void SetupWiFi();
void SetupDisplay();
void callback(char *topic, byte *payload, unsigned int length);

extern WiFiClient wifiClient;
extern PubSubClient client;
extern Bounce bouncer;
extern Adafruit_SSD1306 display;



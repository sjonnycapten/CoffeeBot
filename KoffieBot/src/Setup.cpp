#ifndef test
#define test
#include "Setup.h"
#endif

byte coffeeState = STATE_COFFEE_NOTREADY;
// Initialise the Pushbutton Bouncer object
Bounce bouncer = Bounce();

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(MQTT_SERVER, 1883, wifiClient); // 1883 is the listener port for the Broker

void SetupMQTT()
{

    if (client.connect(CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD))
    {
        Serial.println("Connected to MQTT Broker!");
    }
    else
    {
        Serial.println("Connection to MQTT Broker failed...");
    }
    client.setCallback(callback);
    client.subscribe("buttons");
}

void SetupWiFi()
{
    
    const char* ssid = "HBB";           
    const char* password = "mevrouwwatzoeku"; 
    WiFi.begin(ssid, password);


    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
     if (client.connect(CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD))
    {
        Serial.println("Connected to MQTT Broker!");
        client.publish("buttons", "aanwezig");
    }
    else
    {
        Serial.println("Connection to MQTT Broker failed...");
    }
    client.subscribe("test");
    client.setCallback(callback);
    digitalWrite(WIFI_LED_PIN, LOW);

}

void callback(char *topic, byte *payload, unsigned int length)
{

    Serial.println("callback");
    // Separate the payload in to two nibbles.
    uint8_t command = (*payload & 0x0F);
    uint8_t destination = ((*payload & 0xF0) >> 4);

    Serial.print("destination: ");
    Serial.println(destination, HEX);
    Serial.print("command: ");
    Serial.println(command, HEX);

    HandlePayload(destination, command);
}

void HandlePayload(uint8_t destination, uint8_t command)
{
    Serial.println("test!");
    if (destination == CLIENT_ID_COMPARE || destination == DEST_ALL)
    {

        switch (command)
        {
        case COMMAND_COFFEE_ALERT:
            coffeeState = STATE_COFFEE_MAKING;
            break;
        case COMMAND_COFFEE_STOP:
            coffeeState = STATE_COFFEE_NOTREADY;
            break;
        case COMMAND_COFFEE_REQUEST_ACK:
            coffeeState = STATE_COFFEE_REQUEST_RECEIVED;
        }
    }
}

void sendData(uint8_t command, char *toppic)
{

    // Add the client to client to the comand so the hub knows who has send it.
    uint8_t data = command | CLIENT_ID_MASK;
    if (client.publish(toppic, &data, sizeof(uint8_t)))
    {
        Serial.print(data, HEX);
        Serial.print(" was sended to ");
        Serial.println(toppic);
    }
    // When the publish was not succcesfull reconnect and try again.
    else
    {
        Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
        client.connect(CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD);
        delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
        client.publish(toppic, &data, sizeof(uint8_t));
    }
}

void CheckWiFiConnection()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("lost wifi connection");
        WiFi.disconnect();
        WiFi.reconnect();
    }
}

void SendMessageOnButtonPress(Bounce bouncer)
{
    if (bouncer.rose())
    {

        sendData(COMMAND_COFFEE_REQUEST, TOPPIC_HUB);
    }
}

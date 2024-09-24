#include "Communication.h"
#include "image.h"

bool coffeeReady = false;
int coffeeCount = 0;

//Send the state of the CoffeeKiosk to The MQTT server
void SendCoffeeState()
{
#ifdef MQTT

    if (coffeeReady)
    {
        sendData(COMMAND_COFFEE_ALERT, DEST_ALL, TOPPIC_BUTTONS);
    }

    if (!coffeeReady)
    {
        sendData(COMMAND_COFFEE_STOP, DEST_ALL, TOPPIC_BUTTONS);
        coffeeCount = 0;
    }

#endif
}
//Change the current state of the Coffee Kiosk
void ChangeCoffeeState()
{
    coffeeReady = !coffeeReady;
    SendCoffeeState();

    // Display Text

    display.setCursor(0, 0);
    display.setTextColor(WHITE, BLACK);
    display.println("                          ");
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    if (coffeeReady)
        display.println("zetten");
    if (!coffeeReady)
        display.drawBitmap(0, 0, myBitmap, 128, 64, WHITE);
    display.display();
}



void HandlePayload(uint8_t sender, uint8_t command)
{

    switch (command)
    {
    case COMMAND_COFFEE_REQUEST:
        sendData(COMMAND_COFFEE_REQUEST_ACK,sender,TOPPIC_BUTTONS);
        IncreaseCoffeeCount();
    }
}

void sendData(uint8_t command, uint8_t destination, char *toppic)
{

    // Add the Destination to the comand so the buttons know who has to listen.
    uint8_t data = destination | command;

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

void IncreaseCoffeeCount()
{
    coffeeCount++;
    display.setCursor(0, 28);
    display.setTextColor(WHITE, BLACK);
    display.println("     ");
    display.setTextColor(WHITE);
    display.setCursor(0, 28);

    display.print(coffeeCount);
    Serial.println(coffeeCount);
    display.display();
}


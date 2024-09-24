#include "Setup.h"
// WiFi
#ifdef MQTT

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(MQTT_SERVER, 1883, wifiClient); // 1883 is the listener port for the Broker
#endif

// Initialise the Pushbutton Bouncer object
Bounce bouncer = Bounce();

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void SetupDisplay()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    // Clear the buffer.
    display.clearDisplay();

    // Display Text
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(45, 0);
    display.println("HBB");
    display.setCursor(5, 18);
    display.println("KoffieBot");
    display.setCursor(60, 50);
    display.println("v0.1");   

    display.display();
    display.setTextSize(3);
}

void SetupMQTT()
{
    #ifdef MQTT

    

    // Debugging - Output the IP Address of the ESP32
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (client.connect(CLIENT_ID,MQTT_USERNAME,MQTT_PASSWORD))
    {
        Serial.println("Connected to MQTT Broker!");
        client.publish("buttons", "aanwezig");
    }
    else
    {
        Serial.println("Connection to MQTT Broker failed...");
    }
    client.setCallback(callback);
    client.subscribe("buttons");
    

    digitalWrite(WIFI_LED_PIN,LOW);
    #endif
}
void SetupWiFi()
{
    esp_wifi_set_ps (WIFI_PS_NONE);
    WiFi.begin(SSID,WIFI_PASSWORD);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}



void callback(char *topic, byte *payload, unsigned int length)
{

    // Separate the payload in to two nibbles.    
    uint8_t command = (*payload & 0x0F);
    uint8_t sender = ((*payload & 0xF0));
     

    Serial.print("sender: " );
    Serial.println(sender,HEX);
    Serial.print("command: ");
    Serial.println(command,HEX);

    HandlePayload(sender, command);
    
}
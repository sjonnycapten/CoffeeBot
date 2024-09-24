# CoffeeBot: Smart Dormitory Coffee Notification System

## Overview
CoffeeBot is an MQTT-based notification system designed to streamline coffee-making coordination among dormmates. It uses ESP32-based devices for both individual room buttons and the central hub near the coffee machine, all connected through a Raspberry Pi running a Mosquitto MQTT server.


## How It Works
1. **Initiating Coffee Making**:
   - The coffee maker presses the ESP32 hub button to notify dormmates.
   - ESP32 buttons in each room light up and flash.

2. **Requesting Coffee**:
   - Interested dormmates press their flashing room buttons.
   - The ESP32 hub updates the count of coffee requests.

3. **Coffee Ready Notification**:
   - Once coffee is ready, the maker presses the hub button again.
   - This sends a final notification to all rooms.

## Technology
- MQTT protocol for reliable messaging
- ESP32 microcontrollers for both room buttons and the central hub
- Custom-designed ESP32 hub with display for central control and request tracking
- Raspberry Pi running Mosquitto MQTT server as the central communication node

##### (README Created using Claude)

# A small script to mannualy publis MQTT commands

import paho.mqtt.client as mqtt
import sys

# Don't forget to change the variables for the MQTT broker!
mqtt_username = "USERNAME"
mqtt_password = "PASSWORD"
mqtt_topic = "esp"
mqtt_broker_ip = "192.168.178.100"

client = mqtt.Client()
# Set the username and password for the MQTT client
client.username_pw_set(mqtt_username, mqtt_password)

client.connect(mqtt_broker_ip, 1883)
client.publish('buttons',int(str(sys.args[1]),0))
client.disconnect()

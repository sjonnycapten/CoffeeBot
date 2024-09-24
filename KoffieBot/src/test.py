"""
Python MQTT Subscription client
Thomas Varnish (https://github.com/tvarnish), (https://www.instructables.com/member/Tango172)
Written for my Instructable - "How to use MQTT with the Raspberry Pi and ESP8266"
"""
import paho.mqtt.client as mqtt
import sys

# Don't forget to change the variables for the MQTT broker!
mqtt_username = "sjonnycapten"
mqtt_password = "mevrouwwatzoeku"
mqtt_topic = "esp"
mqtt_broker_ip = "192.168.178.100"

client = mqtt.Client()
# Set the username and password for the MQTT client
client.username_pw_set(mqtt_username, mqtt_password)

client.connect(mqtt_broker_ip, 1883)
client.publish('esp',str(sys.args[1]))
client.disconnect()

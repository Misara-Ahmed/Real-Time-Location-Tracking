# Importing important MQTT libraries
import paho.mqtt.client as paho
from paho import mqtt

# HiveMQ broker details
url = "6b156a30cf464e68842b90357f944402.s1.eu.hivemq.cloud"     # HiveMQ Cluster URL
port = 8883                                                     # Default MQTT port
topic = "esp32/rssi"

# Authentication credentials
username = "Misara-Ahmed"
password = "Miso-229"

# Defining callback functions for different events
def on_connect(client, userdata, flags, rc, properties=None):
    print("CONNACK received with code %s." % rc)

# Function to print the received message
def on_message(client, userdata, msg):
    # print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))
    print(int(msg.payload))

client = paho.Client(client_id="", userdata=None, protocol=paho.MQTTv5)

# Enable TLS for secure connection
client.tls_set(tls_version=mqtt.client.ssl.PROTOCOL_TLS)

# Set username and password
client.username_pw_set(username, password)

# Connect to HiveMQ Cloud
client.connect(url, port)

# Setting callbacks
client.on_message = on_message
client.on_connect = on_connect

# Subscribe to the needed topic
client.subscribe(topic)

# Looping forever to maintain connection with the cloud
client.loop_forever()
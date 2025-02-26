# import paho.mqtt.client as mqtt
#
# # HiveMQ broker details
# broker = "broker.hivemq.com"  # Public HiveMQ broker
# port = 1883  # Default MQTT port (unencrypted)
# topic = "esp32/rssi"  # Replace with your topic
#
# # Authentication credentials
# username = "Misara-Ahmed"
# password = "Miso-229"
#
# # Callback when the client connects to the broker
# def on_connect(client, userdata, flags, rc):
#     print(f"Connected with result code {rc}")
#     # Subscribe to the topic after connecting
#     client.subscribe(topic)
#
# # Callback when a message is received from the broker
# def on_message(client, userdata, msg):
#     print(f"Received message: {msg.payload.decode()} on topic {msg.topic}")
#     # Process the message (e.g., extract a specific value)
#     value = msg.payload.decode()  # Assuming the payload is a string
#     print(f"Retrieved value: {value}")
#
# # Create an MQTT client instance
# client = mqtt.Client()
#
# # Set authentication credentials
# client.username_pw_set(username, password)
#
# print(client.connect("6b156a30cf464e68842b90357f944402.s1.eu.hivemq.cloud", 8883))
# print(client.connect(broker, port))
#
# print("hello")
#
# print(client.subscribe(topic, qos=0))

# # Assign callback functions
# client.on_connect = on_connect
# client.on_message = on_message
#
# # Connect to the HiveMQ broker
# client.connect(broker, port, 60)

# Start the loop to process network traffic and dispatch callbacks
# client.loop_forever()





# import paho.mqtt.client as mqtt
#
# # Authentication credentials
# username = "Misara-Ahmed"
# password = "Miso-229"
#
# topic = "esp32/rssi"  # Replace with your topic
# broker = "broker.hivemq.com"  # Public HiveMQ broker
# port = 1883  # Default MQTT port (unencrypted)
#
# # Callback function to handle incoming MQTT messages
# def on_message(client, userdata, message):
#     print(f"Received message: {message.payload.decode()} on topic {message.topic}")
#     # Process the message (e.g., store it, trigger an action)
#     process_message(message.payload.decode())
#
# def process_message(message):
#     print(f"Processing message: {message}")
#
# # Create an MQTT client instance
# client = mqtt.Client(client_id="", userdata=None, protocol=mqtt.MQTTv5)
# print (client)
#
# client.tls_set(tls_version=mqtt.client.ssl.PROTOCOL_TLS)
# # Set authentication credentials
# client.username_pw_set(username, password)
#
# # Assign the callback function
# client.on_message = on_message
#
# # Connect to the MQTT broker
# client.connect("6b156a30cf464e68842b90357f944402.s1.eu.hivemq.cloud", 8883)
# # client.connect(broker, port)
#
# # Subscribe to a topic
# # print(client.subscribe(topic, 0))
# client.subscribe("esp32/rssi", qos=0)
# # Start the loop to process network traffic and dispatch callbacks
# client.loop_forever()






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

# Setting callbacks for different events to see if it works, print the message etc.
def on_connect(client, userdata, flags, rc, properties=None):
    print("CONNACK received with code %s." % rc)

# Print message, useful for checking if it was successful
def on_message(client, userdata, msg):
    # print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))
    print(int(msg.payload))

# using MQTT version 5 here, for 3.1.1: MQTTv311, 3.1: MQTTv31
# userdata is user defined data of any type, updated by user_data_set()
# client_id is the given name of the client
client = paho.Client(client_id="", userdata=None, protocol=paho.MQTTv5)
client.on_connect = on_connect

# enable TLS for secure connection
client.tls_set(tls_version=mqtt.client.ssl.PROTOCOL_TLS)
# set username and password
client.username_pw_set(username, password)
# connect to HiveMQ Cloud on port 8883 (default for MQTT)
client.connect(url, port)

# setting callbacks, use separate functions like above for better visibility
client.on_message = on_message

# subscribe to the needed topic
client.subscribe(topic)

# loop_forever
client.loop_forever()
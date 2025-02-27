# # Importing important MQTT libraries
# import paho.mqtt.client as paho
# from paho import mqtt
#
# # HiveMQ broker details
# url = "6b156a30cf464e68842b90357f944402.s1.eu.hivemq.cloud"     # HiveMQ Cluster URL
# port = 8883                                                     # Default MQTT port
# topic = "esp32/rssi"
#
# # Authentication credentials
# username = "Misara-Ahmed"
# password = "Miso-229"
#
# # Defining callback functions for different events
# def on_connect(client, userdata, flags, rc, properties=None):
#     print("CONNACK received with code %s." % rc)
#
# # Function to print the received message
# def on_message(client, userdata, msg):
#     # print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))
#     print(int(msg.payload))
#
# client = paho.Client(client_id="", userdata=None, protocol=paho.MQTTv5)
#
# # Enable TLS for secure connection
# client.tls_set(tls_version=mqtt.client.ssl.PROTOCOL_TLS)
#
# # Set username and password
# client.username_pw_set(username, password)
#
# # Connect to HiveMQ Cloud
# client.connect(url, port)
#
# # Setting callbacks
# client.on_message = on_message
# client.on_connect = on_connect
#
# # Subscribe to the needed topic
# client.subscribe(topic)
#
# # Looping forever to maintain connection with the cloud
# client.loop_forever()
########################################################################################################################


#####################################  Simple window and point moving  #################################################
# import tkinter as tk
# import paho.mqtt.client as mqtt
# from threading import Thread
#
# # Global variables
# current_location = [0, 0]  # Initial location (latitude, longitude)
# canvas_size = 1000  # Size of the canvas (400x400 pixels)
#
#
# # MQTT Callbacks
# def on_connect(client, userdata, flags, rc):
#     print("Connected to MQTT broker")
#     client.subscribe("location/topic")  # Subscribe to the location topic
#
#
# def on_message(client, userdata, msg):
#     global current_location
#     # Parse the location data (format: "latitude,longitude")
#     latitude, longitude = map(float, msg.payload.decode().split(','))
#     current_location = [latitude, longitude]
#     print(f"Updated location: {current_location}")
#
#     # Update the dot position on the canvas
#     update_dot_position()
#
#
# # Function to update the dot position on the canvas
# def update_dot_position():
#     # Convert latitude and longitude to canvas coordinates
#     x = (current_location[1] + 180) * (canvas_size / 360)  # Longitude to X
#     y = (90 - current_location[0]) * (canvas_size / 180)  # Latitude to Y
#
#     # Move the dot to the new position
#     canvas.coords(dot, x - 5, y - 5, x + 5, y + 5)  # Dot size: 10x10 pixels
#
#
# # MQTT Client Setup
# client = mqtt.Client()
# client.on_connect = on_connect
# client.on_message = on_message
# client.connect("broker.hivemq.com", 1883, 60)  # Connect to the MQTT broker
#
# # Start the MQTT loop in a separate thread
# mqtt_thread = Thread(target=client.loop_forever)
# mqtt_thread.daemon = True
# mqtt_thread.start()
#
# # Create the Tkinter UI
# root = tk.Tk()
# root.title("Real-Time Location Indicator")
#
# # Create a canvas to display the dot
# canvas = tk.Canvas(root, width=canvas_size, height=canvas_size, bg="white")
# canvas.pack()
#
# # Draw the initial dot at the center of the canvas
# dot = canvas.create_oval(510, 510, 500, 500, fill="blue")  # Initial position: center
# canvas.create_rectangle(450,1000,550,950, fill="red")
# canvas.create_text(500,975, text="Router", font=("Verdana", 15, "bold"))
#
# # Run the Tkinter main loop
# root.mainloop()
########################################################################################################################


######################################  Responsive window and point  ###################################################
# import tkinter as tk
#
# # Create the main window
# root = tk.Tk()
# root.title("Responsive Window")
#
# width = 200
# height = 150
#
# # Make the window resizable
# root.geometry("400x300")
# root.minsize(width, height)  # Set a minimum window size
# def update_dot():
#     width = root.winfo_width()  # Get current window width
#     height = root.winfo_height()  # Get current window height
#     canvas.coords(dot, (width/2), (width/2) , (height/2) + 10, (height/2) + 10)  # Dot size: 10x10 pixels
#     # if (curr_height != height) | (curr_width != width):
#     #     canvas.create_oval(100 * width / 2, 100 * width / 2, 150 * height / 2, 150 * height / 2, fill="red")
#     root.after(100, update_dot)  # Update every 100ms
#
# # Create a canvas that fills the window
# canvas = tk.Canvas(root, bg="white")
# canvas.pack(fill=tk.BOTH, expand=True)  # Fill and expand with window
#
# # Add a dot to the canvas
# dot = canvas.create_oval(100*width/2 , 100*width/2, 150*height/2, 150*height/2, fill="red")
#
#
# update_dot()
#
# # Run the Tkinter main loop
# root.mainloop()
########################################################################################################################
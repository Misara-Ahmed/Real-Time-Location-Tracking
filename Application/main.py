import tkinter as tk
import threading
from PIL import Image, ImageTk
import mysql.connector
import paho.mqtt.client as paho
from paho import mqtt

# HiveMQ broker details
url = "6b156a30cf464e68842b90357f944402.s1.eu.hivemq.cloud"     # HiveMQ Cluster URL
port = 8883                                                     # Default MQTT port
topic = "esp32/rssi"

# Authentication credentials
username = "Misara-Ahmed"
password = "Miso-229"

# Database details using MYSQL
mydb = mysql.connector.connect(
  host="localhost",
  user="root",
  passwd="miso246",
  database="location_tracking"
)
mycursor = mydb.cursor()

#### Create a table in the database if not existed ####
# mycursor.execute("""
#     CREATE TABLE IF NOT EXISTS loc_map (
#         id INT AUTO_INCREMENT PRIMARY KEY,
#         location VARCHAR(50) NOT NULL,
#         ap1_rssi INT NOT NULL,
#         ap2_rssi INT NOT NULL,
#         ap3_rssi INT NOT NULL
#     )
# """)

# Retrieve data from the database
mycursor.execute("SELECT * FROM loc_map")
rows = mycursor.fetchall()  # Fetch all rows

# Define the map image and room coordinates
MAP_IMAGE = "map.png"  # Path to the map image
ROOM_COORDINATES = {
    "Room A": (100, 225),
    "Room B": (300, 100),
    "Corridor": (300, 300),
    "Salon": (100, 400)
}

# Initialize the estimated location (default)
estimated_location = "Room A"

# Function to match the current location with the saved locations in the database
def estimateLocation(rssi_1, rssi_2, rssi_3):
    # Intialize variables
    min_distance = 10000000000000
    location = "Unkown"

    for row in rows:
        # Calculating the nearest location to the current location using RSSI values
        distance = abs(rssi_1 - row[2]) + abs(rssi_2 - row[3]) + abs(rssi_3 - row[4])
        if distance < min_distance:
            min_distance = distance
            location = row[1]

    return location

# Function to update the arrow position
def update_arrow():
    global estimated_location

    # Get the coordinates of the estimated location
    x, y = ROOM_COORDINATES[estimated_location]

    # Define the arrow shape (triangle) around the coordinates
    arrow_coords = [
        x, y - 10,          # Top point
        x - 10, y + 10,     # Bottom-left point
        x + 10, y + 10,     # Bottom-right point
    ]

    # Move the arrow to the new position
    canvas.coords(arrow, arrow_coords)

    # Update the location label
    location_label.config(text=f"Estimated Location: {estimated_location}")

# Defining callback functions for different events
def on_connect(client, userdata, flags, rc, properties=None):
    print("CONNACK received with code %s." % rc)

# Function to do certain action when receiving msg
def on_message(client, userdata, msg):
    global estimated_location
    rssi_1, rssi_2 , rssi_3 = map(int, msg.payload.decode().split(','))

    #### This part of code is used in online mode while estimating the current location ####
    estimated_location = estimateLocation(rssi_1, rssi_2, rssi_3)
    print(estimated_location)
    update_arrow()

    #### This part of code is used in offline mode while building the map ####

    # Insert data into the table
    # sql = """
    #     INSERT INTO loc_map (location, ap1_rssi, ap2_rssi, ap3_rssi)
    #     VALUES (%s, %s, %s, %s)
    # """
    # values = ("Salon", rssi_1, rssi_2, rssi_3)
    # mycursor.execute(sql, values)
    # mydb.commit()
    # print("Adding to database is done.")

# Function to start the MQTT client in another thread
def start_mqtt_client():
    client = paho.Client(client_id="", userdata=None, protocol=paho.MQTTv5)

    # Enable TLS for secure connection
    client.tls_set(tls_version=mqtt.client.ssl.PROTOCOL_TLS)

    # Set username and password
    client.username_pw_set(username, password)

    # Connect to HiveMQ Cloud
    client.connect(url, port)

    # Subscribe to the needed topic
    client.subscribe(topic)

    # Setting callbacks
    client.on_message = on_message
    client.on_connect = on_connect

    # Looping forever to maintain connection with the cloud
    client.loop_forever()

# Create the main window
root = tk.Tk()
root.title("Real-Time Location Tracking")

# Load the saved map image
map_image = Image.open(MAP_IMAGE)
map_photo = ImageTk.PhotoImage(map_image)

# Create a canvas to display the map and arrow
canvas = tk.Canvas(root, width=map_image.width, height=map_image.height)
canvas.pack()

# Add the map image to the canvas
canvas.create_image(0, 0, anchor=tk.NW, image=map_photo)

# Add an arrow (triangle) to represent the estimated location
x, y = ROOM_COORDINATES[estimated_location]
arrow_coords = [
    x, y - 10,          # Top point
    x - 10, y + 10,     # Bottom-left point
    x + 10, y + 10,     # Bottom-right point
]

# Initialize the arrow
arrow = canvas.create_polygon(arrow_coords, fill="red")  

# Add a label to display the estimated location
location_label = tk.Label(root, text=f"Estimated Location: {estimated_location}", font=("Arial", 14))
location_label.pack(pady=10)

# Start the MQTT client in a separate thread
mqtt_thread = threading.Thread(target=start_mqtt_client, daemon=True)
mqtt_thread.start()

# Run the Tkinter main loop
root.mainloop()

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
#     width = root.winfo_width()    # Get current window width
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
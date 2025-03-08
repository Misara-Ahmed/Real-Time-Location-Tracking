# Real-Time Location Tracking System 📍

🚀 A real-time location tracking system using **ESP32**, **MQTT**, and **Python**. Track moving objects on a live map with precision! 🗺️

## Features
- 📡 **ESP32** for real-time location updates.
- 🌐 **MQTT** for communication between devices.
- 🖥️ **Python GUI** for visualizing location on a map.
- 📍 **Live Arrow** to track the object's movement.

## How It Works
1. The ESP32 publishes location updates to an MQTT topic.
2. The Python GUI subscribes to the topic and updates the arrow position on the map in real-time.

## Requirements
- ESP32 with Wi-Fi.
- MQTT Broker (e.g., HiveMQ, Mosquitto).
- Python 3.x with Tkinter and Paho-MQTT.

## Setup
1. Flash the ESP32 with the provided code.
2. Run the Python GUI script.
3. Watch the object move on the map in real-time! 🎯

## Screenshots
![Map Screenshot](screenshot.png)

## License
MIT License - Feel free to use and modify! 🚀

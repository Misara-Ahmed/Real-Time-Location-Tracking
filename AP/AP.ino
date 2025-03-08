// Important includes
#include <WiFi.h>

// Define the SSID and password for the access point
const char* ssid = "AP_1";
const char* password = "12345678";

void setup() {
  // Start Serial communication
  Serial.begin(115200);

  // Configure the ESP32 as an access point
  WiFi.softAP(ssid, password);
}

void loop() {}
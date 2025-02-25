// #include <WiFi.h>

// // Replace with your network credentials (STATION)
// const char* ssid = "Ahmed Said";
// const char* password = "missarahmed@246";

// void initWiFi() {
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(ssid, password);
//   Serial.print("Connecting to WiFi ..");
//   while (WiFi.status() != WL_CONNECTED) {
//     Serial.print('.');
//     delay(1000);
//   }
//   Serial.println(WiFi.localIP());
// }

// void setup() {
//   Serial.begin(115200);
//   initWiFi();
// }

// void loop()
// {
//   Serial.print("RRSI: ");
//   Serial.println(WiFi.RSSI());
//   delay(500);
// }

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Wi-Fi credentials
const char* ssid = "Ahmed Said";
const char* password = "missarahmed@246";

// MQTT broker settings
const char* mqtt_server = "6b156a30cf464e68842b90357f944402.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_username = "Misara-Ahmed";
const char* mqtt_password = "Miso-229";

// MQTT topic to publish in
const char* clientID = "ESP32"
const char* topic = "esp32/rssi";

// Create client instances
WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);

// Variables for timing
long previous_time = 0;

void setupMQTT()
{
  mqttClient.setServer(mqtt_server, mqtt_port);
}

void reconnect()
{
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected())
  {
    Serial.println("Reconnecting to MQTT Broker...");
    
    if (mqttClient.connect(clientID, mqtt_username, mqtt_password))
    {
      Serial.println("Connected to MQTT Broker.");
    } 
    else
    {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to Wi-Fi");

  // Initialize secure WiFiClient
  wifiClient.setInsecure(); // Use this only for testing, it allows connecting without a root certificate
  
  setupMQTT();
}

void loop()
{
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

  long now = millis();
  if (now - previous_time > 1000) { // Publish every 10 seconds
    previous_time = now;

    // Read the IR sensor value
    int ir_sensor_value = analogRead(ir_sensor_pin);
    int distance = map(ir_sensor_value, 0, 4095, 0, 30);
    
    // Convert the value to a string
    String ir_value_str = String(distance);
    
    // Publish the sensor value to the MQTT topic
    Serial.print("IR Sensor Value: ");
    Serial.println(ir_value_str);
    mqttClient.publish(topic_publish_ir, ir_value_str.c_str());
  }
}
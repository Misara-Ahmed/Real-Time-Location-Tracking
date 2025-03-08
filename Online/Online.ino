// Important includes
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// MQTT broker settings
const char* mqtt_server = "6b156a30cf464e68842b90357f944402.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_username = "Misara-Ahmed";
const char* mqtt_password = "Miso-229";

// MQTT topic to publish in
const char* clientID = "ESP32";
const char* topic = "esp32/rssi";

// Create client instances
WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);

// Wi-Fi credentials
const char* ssid_1 = "AP_1";
const char* password_1 = "12345678";

const char* ssid_2 = "AP_2";
const char* password_2 = "12345678";

const char* ssid_3 = "Ahmed Said";
const char* password_3 = "missarahmed@246";

// RSSI values for each access point
int rssi_1 = 0;
int rssi_2 = 0;
int rssi_3 = 0;

// Counter for the access points
char ap = 0;

// Var to hold the number of found  networks
int num_networks = 0;

void setup()
{
  // Begin serial connection
  Serial.begin(2000000);

  // Setup wifi mode as station
  WiFi.mode(WIFI_STA);

  // Initialize secure WiFiClient
  wifiClient.setInsecure();

  // Setup MQTT connection
  setupMQTT();

  // Connect to the AP
  connect(ssid_3,password_3);
}

void loop()
{
  // Check if connected to the MQTT broker
  if (!mqttClient.connected())
  {
    reconnect();
  }

  // Maintain connection with MQTT broker
  mqttClient.loop();

  // Scan for nearby networks
  num_networks = WiFi.scanNetworks();

  // Looping till finding the required APs
  for (int i=0 ; i<num_networks ; i++)
  {
    if(ap == 3)
    {
      ap=0;
      break;
    }
    else if (WiFi.SSID(i) == ssid_1)
    {
      rssi_1 = WiFi.RSSI(i);
      ap++;
    }
    else if (WiFi.SSID(i) == ssid_2)
    {
      rssi_2 = WiFi.RSSI(i);
      ap++;
    }
    else if (WiFi.SSID(i) == ssid_3)
    {
      rssi_3 = WiFi.RSSI(i);
      ap++;
    }
  }

  Serial.print("AP1: ");
  Serial.print(rssi_1);
  Serial.print(" dBm, AP2: ");
  Serial.print(rssi_2);
  Serial.print(" dBm, AP3: ");
  Serial.print(rssi_3);
  Serial.println(" dBm");

  // Convert the RSSI values to a string
  String payload = String(rssi_1) + "," + String(rssi_2) + "," + String(rssi_3);

  // Publish the RSSI values to the MQTT topic
  mqttClient.publish(topic, payload.c_str());
}

// Function to setup the connection to the MQTT broker
void setupMQTT()
{
  mqttClient.setServer(mqtt_server, mqtt_port);
}

// Function to make sure of the connection to the MQTT broker
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

// Function to connect to a specific network (AP)
void connect(const char* ssid, const char* password)
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED);
}

// Important includes
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#define NUM_READINGS                      20

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

// An array for each access point to store the rssi values used at each point.
int ap_1[NUM_READINGS];
int ap_2[NUM_READINGS];
int ap_3[NUM_READINGS];

// Average for the stored values for each access point
int avg_1 = 0;
int avg_2 = 0;
int avg_3 = 0;

// a counter
char count = 0;

void setup()
{
  // Begin serial connection
  Serial.begin(2000000);

  // Setup wifi mode as station
  WiFi.mode(WIFI_STA);
}

void loop()
{
  // Handling values after being stored
  if(count == NUM_READINGS)
  {
    // Calculating average of values after being stored 
    for(char i=0 ; i<NUM_READINGS ; i++)
    {
      avg_1 += ap_1[i];
      avg_2 += ap_2[i];
      avg_3 += ap_3[i];
    }
    avg_1 /= NUM_READINGS;
    avg_2 /= NUM_READINGS;
    avg_3 /= NUM_READINGS;

    // Initialize secure WiFiClient
    wifiClient.setInsecure();

    // Setup MQTT connection
    setupMQTT();

    // Check if connected to the MQTT broker
    if (!mqttClient.connected())
    {
      reconnect();
    }

    // Maintain connection with MQTT broker
    mqttClient.loop();

    // Convert the RSSI values to a string
    String payload = String(avg_1) + "," + String(avg_2) + "," + String(avg_3);

    // Publish the RSSI values to the MQTT topic
    mqttClient.publish(topic, payload.c_str());
    Serial.println("First Point Done");
    delay(2000);
    count = 0;
  }
  else
  {
    // Connecting to each AP and storing the RSSI value in the array
    connect(ssid_1,password_1);
    ap_1[count] = WiFi.RSSI();
    Serial.print("AP1: ");
    Serial.print(ap_1[count]);

    connect(ssid_2,password_2);
    ap_2[count] = WiFi.RSSI();
    Serial.print(" dBm, AP2: ");
    Serial.print(ap_2[count]);

    connect(ssid_3,password_3);
    ap_3[count] = WiFi.RSSI();
    Serial.print(" dBm, AP3: ");
    Serial.print(ap_3[count]);
    Serial.println(" dBm");

    count++;
  }
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

  // Bloking till connecting to the network
  while (WiFi.status() != WL_CONNECTED);
}
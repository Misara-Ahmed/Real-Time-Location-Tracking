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

// Variables for timing
long previous_time = 0;

// Wi-Fi credentials
const char* ssid_1 = "AP_1";
const char* password_1 = "12345678";

const char* ssid_2 = "AP_2";
const char* password_2 = "12345678";

const char* ssid_3 = "Ahmed Said";
const char* password_3 = "missarahmed@246";

int ap_1[20];
int ap_2[20];
int ap_3[20];

int avg_1 = 0;
int avg_2 = 0;
int avg_3 = 0;

char count = 0;


void setup()
{
  Serial.begin(2000000);
  WiFi.mode(WIFI_STA);
}

void loop()
{
  if(count == 20)
  {
    //count = 0;
    for(char i=0 ; i<20 ; i++)
    {
      avg_1 += ap_1[i];
      avg_2 += ap_2[i];
      avg_3 += ap_3[i];
    }
    avg_1 /= 20;
    avg_2 /= 20;
    avg_3 /= 20;

    // Initialize secure WiFiClient
    wifiClient.setInsecure(); // Use this only for testing, it allows connecting without a root certificate
  
    setupMQTT();

    if (!mqttClient.connected())
    {
      reconnect();
    }

    mqttClient.loop();

    // Convert the RSSI values to a string
    String payload = String(avg_1) + "," + String(avg_2) + "," + String(avg_3);

    // Publish the sensor value to the MQTT topic
    // Serial.print("RSSI Value: ");
    // Serial.println(rssi_str);
    mqttClient.publish(topic, payload.c_str());
  }
  else
  {
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

void connect(const char* ssid, const char* password)
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED);
}
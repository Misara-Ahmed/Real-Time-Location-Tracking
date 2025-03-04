// #include <WiFi.h>
// #include <WiFiClientSecure.h>
// #include <PubSubClient.h>

// // Wi-Fi credentials
// const char* ssid = "Ahmed Said";
// const char* password = "missarahmed@246";

// // MQTT broker settings
// const char* mqtt_server = "6b156a30cf464e68842b90357f944402.s1.eu.hivemq.cloud";
// const int mqtt_port = 8883;
// const char* mqtt_username = "Misara-Ahmed";
// const char* mqtt_password = "Miso-229";

// // MQTT topic to publish in
// const char* clientID = "ESP32";
// const char* topic = "esp32/rssi";

// // Create client instances
// WiFiClientSecure wifiClient;
// PubSubClient mqttClient(wifiClient);

// // Variables for timing
// long previous_time = 0;

// void setup()
// {
//   Serial.begin(115200);

//   initWiFi();

//   // Initialize secure WiFiClient
//   wifiClient.setInsecure(); // Use this only for testing, it allows connecting without a root certificate
  
//   setupMQTT();
// }

// void loop()
// {
//   if (!mqttClient.connected())
//   {
//     reconnect();
//   }
//   mqttClient.loop();

//   // Publish every 500 milliseconds (0.5 sec)
//   long now = millis();
//   if (now - previous_time > 500)
//   {
//     previous_time = now;
//     int rssi = WiFi.RSSI();

//     // Convert the RSSI value to a string
//     String rssi_str = String(rssi);
    
//     // Publish the sensor value to the MQTT topic
//     Serial.print("RSSI Value: ");
//     Serial.println(rssi_str);
//     mqttClient.publish(topic, rssi_str.c_str());
//   }
// }

// void initWiFi()
// {
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(ssid, password);
//   Serial.print("Connecting to WiFi ..");
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     Serial.print('.');
//     delay(500);
//   }
//   Serial.println("");
//   Serial.println("Connected Successfully");
// }

// void setupMQTT()
// {
//   mqttClient.setServer(mqtt_server, mqtt_port);
// }

// void reconnect()
// {
//   Serial.println("Connecting to MQTT Broker...");
//   while (!mqttClient.connected())
//   {
//     Serial.println("Reconnecting to MQTT Broker...");
    
//     if (mqttClient.connect(clientID, mqtt_username, mqtt_password))
//     {
//       Serial.println("Connected to MQTT Broker.");
//     } 
//     else
//     {
//       Serial.print("Failed, rc=");
//       Serial.print(mqttClient.state());
//       Serial.println(" try again in 5 seconds");
//       delay(5000);
//     }
//   }
// }


// #include <WiFi.h>

// // Define the SSID(name) and password for the access point
// const char* ssid = "AP_2";
// const char* password = "12345678";

// void setup()
// {
//   Serial.begin(115200);
//   Serial.println();

//   // Configure the ESP32 as an access point
//   WiFi.softAP(ssid, password);
// }

// void loop(){}

// #include <WiFi.h>

// // Wi-Fi credentials
// const char* ssid_1 = "AP_1";
// const char* password_1 = "12345678";

// // Wi-Fi credentials
// const char* ssid_2 = "AP_2";
// const char* password_2 = "12345678";

// // Wi-Fi credentials
// const char* ssid = "Ahmed Said";
// const char* password = "missarahmed@246";

// void setup()
// {
//   Serial.begin(2000000);
//   WiFi.mode(WIFI_STA);
// }

// void loop()
// {
//   int rssi_1, rssi_2, rssi_3;  // Default RSSI values
//   char ap = 0;
//   // Scan for nearby networks
//   int num_networks = WiFi.scanNetworks();
//   // Serial.println(num_networks);



//   // Print the RSSI values
//   Serial.print("RSSI Values: ");
//   Serial.print("AP1: ");
//   Serial.print(rssi_1);
//   Serial.print(" dBm, AP2: ");
//   Serial.print(rssi_2);
//   Serial.print(" dBm, AP3: ");
//   Serial.print(rssi_3);
//   Serial.println(" dBm");

//   // connect(ssid,password);
//   // rssi_3 = WiFi.RSSI();

//   // connect(ssid_1,password_1);
//   // rssi_1 = WiFi.RSSI();

//   // connect(ssid_2,password_2);
//   // rssi_2 = WiFi.RSSI();
  
//   // Convert the RSSI value to a string
//   // String rssi_str = String(rssi);

//   Print the RSSI values
//   Serial.print("RSSI Values: ");
//   Serial.print("AP1: ");
//   Serial.print(rssi_1);
//   Serial.print(" dBm, AP2: ");
//   Serial.print(rssi_2);
//   Serial.print(" dBm, AP3: ");
//   Serial.print(rssi_3);
//   Serial.println(" dBm");
// // // Publish the sensor value to the MQTT topic
//   // Serial.print("RSSI Value: ");
//   // Serial.println(rssi_str);
// }




// void connect(const char* ssid, const char* password)
// {
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED);
// }



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

int rssi_1 = 0;
int rssi_2 = 0;
int rssi_3 = 0;

char ap = 0;

int num_networks = 0;

void setup()
{
  Serial.begin(2000000);
  WiFi.mode(WIFI_STA);

  // Initialize secure WiFiClient
  wifiClient.setInsecure(); // Use this only for testing, it allows connecting without a root certificate

  setupMQTT();


  connect(ssid_3,password_3);
}

void loop()
{
  if (!mqttClient.connected())
  {
    reconnect();
  }
  mqttClient.loop();

  // Scan for nearby networks
  num_networks = WiFi.scanNetworks();

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
  // connect(ssid_1,password_1);
  // rssi_1 = WiFi.RSSI();
  Serial.print("AP1: ");
  Serial.print(rssi_1);

  // connect(ssid_2,password_2);
  // rssi_2 = WiFi.RSSI();
  Serial.print(" dBm, AP2: ");
  Serial.print(rssi_2);

  // connect(ssid_3,password_3);
  // rssi_3 = WiFi.RSSI();
  Serial.print(" dBm, AP3: ");
  Serial.print(rssi_3);
  Serial.println(" dBm");

  // Convert the RSSI values to a string
  String payload = String(rssi_1) + "," + String(rssi_2) + "," + String(rssi_3);

  // Publish the sensor value to the MQTT topic
  // Serial.print("RSSI Value: ");
  // Serial.println(rssi_str);
  mqttClient.publish(topic, payload.c_str());
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

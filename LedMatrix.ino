/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <ESP8266WiFi.h>
#include "LedMatrix.h"
#include "SimpleTimer.h"
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>


WiFiClient espClient;
PubSubClient mqttClient(espClient);



LedMatrix ledmatrix;
/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "munichmakerlab"
#define WLAN_PASS       "h4ckingr00m"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "broker.mqttdashboard.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "ledmatrix"
#define AIO_KEY         "ledmatrix"
#define AIO_TOPIC "testtopic/ledmatrix"


#define HOSTNAME "LEDMATRIX-"
#define OTA_PASS "1234"

const char* mqtt_server = AIO_SERVER;


void MQTT_connect();

void setup() {
  ledmatrix.toggleWC(0);
  Serial.begin(115200);
  ledmatrix.setText("Munich Maker Lab");
  delay(10);

  Serial.println(F("MQTT LED-Matrix"));
  String hostname(HOSTNAME);
  hostname += String(ESP.getChipId(), HEX);
  WiFi.hostname(hostname);

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  Serial.println("Hostname: " + hostname);




  ledmatrix.startScroll();
  // Start OTA server.
  ArduinoOTA.setHostname((const char *)hostname.c_str());
  ArduinoOTA.setPassword((const char *)OTA_PASS);
  ArduinoOTA.begin();
  // Mqtt
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callback);
}



void loop() {


  mqttClient.loop();

  if (!mqttClient.connected()) {
    reconnectMqtt();
  }


  ledmatrix.loop();

  ArduinoOTA.handle();
  system_soft_wdt_feed();


}



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  char text[length];  
  strncpy(text, (char*)payload, length);
  text[length] = 0;
  Serial.print(text);
  String cmd = String((char *)text);
  ledmatrix.setText(cmd);
  
  Serial.println();  



}
void reconnectMqtt() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect("ESP8266Client12312")) {
      Serial.println("connected");

      // ... and resubscribe
      mqttClient.subscribe(AIO_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

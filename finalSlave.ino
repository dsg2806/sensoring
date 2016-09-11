//Copyright (c) 2016 Dylan Sanusi-Goh & Ethan Payne
//Written by Dylan Sanusi-Goh & Ethan Payne under The MIT License


#include <Wire.h>
#include "Adafruit_MCP9808.h"
#include <Adafruit_ADS1015.h>
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
Adafruit_ADS1015 ads; 

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define wifi_ssid "guest-wireless"
//#define wifi_password "WIFI PASSWORD"

#define mqtt_server "YOUR_MQTT_SERVER_HOST"
#define test_topic "/test/valuesender"

#define humidity_topic "sensor/humidity"
#define temperature_topic "sensor/temperature"

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}





void setup() {
  Serial.begin(9600);
  Serial.println("MCP9808 demo");
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  ads.begin();
  if (!tempsensor.begin(0x18)) {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

bool checkBound(float newValue, float prevValue, float maxDiff) {
  return newValue < prevValue - maxDiff || newValue > prevValue + maxDiff;
}

float testvalue = 34.45;

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

if ((millis() % 10000) == 0) {
Serial.println("wake up MCP9808.... "); // wake up MSP9808 - power consumption ~200 mikro Ampere

  tempsensor.shutdown_wake(0);   
  float c = tempsensor.readTempC();
  delay(1000);
  tempsensor.shutdown_wake(1); 
  int16_t adc0, adc1, adc2, adc3;
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  String result = String(adc0) + "," + String(adc1) + "," + String(c); 
  client.publish(test_topic, result.c_str(), true);

  }
  
  

}

//Copyright (c) 2016 Dylan Sanusi-Goh & Ethan Payne
//Written by Dylan Sanusi-Goh & Ethan Payne under The MIT License

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include <Adafruit_HDC1000.h>
#include <MCP3008.h>
#include "Adafruit_HDC1000.h"

#define wifi_ssid "guest-wireless"
//#define wifi_password "WIFI PASSWORD"

#define mqtt_server "YOUR_MQTT_SERVER_HOST"
#define test_topic "/test/valuesender"

#define humidity_topic "sensor/humidity"
#define temperature_topic "sensor/temperature"

#define CS_PIN 15 
#define CLOCK_PIN 14 
#define MOSI_PIN 13 
#define MISO_PIN 12 

WiFiClient espClient;
PubSubClient client(espClient);

int sound = A0;
Adafruit_HDC1000 hdc = Adafruit_HDC1000();

MCP3008 adc(CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
#define Serial SerialUSB
#endif

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

  // open serial port
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  pinMode(sound, INPUT);
  if (!hdc.begin()) {
    Serial.println("Couldn't find sensor!");
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

  if ((millis() % 1000) == 0) {

    int valLIGHT = adc.readADC(0); // read Chanel 0 from MCP3008 ADC
    Serial.print("New test value:");
    Serial.println(String(testvalue).c_str());
    client.publish(test_topic, String(valLIGHT).c_str(), true);
    client.publish(test_topic, String(analogRead(sound)).c_str(), true);
    client.publish(test_topic, String(analogRead(sound)).c_str(), true);
    client.publish(test_topic, String(hdc.readTemperature()).c_str(), true);
    client.publish(test_topic, String(hdc.readHumidity()).c_str(), true);
  }


  delay(500);

}

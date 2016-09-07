#include <Wire.h>
#include "Adafruit_MCP9808.h"
#include <Adafruit_ADS1015.h>
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
Adafruit_ADS1015 ads; 

void setup() {
  Serial.begin(9600);
  Serial.println("MCP9808 demo");
  
  ads.begin();
  if (!tempsensor.begin(0x18)) {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
}

void loop() {
  Serial.println("wake up MCP9808.... "); // wake up MSP9808 - power consumption ~200 mikro Ampere

  tempsensor.shutdown_wake(0);   
  float c = tempsensor.readTempC();
  //Serial.print("Temp: "); Serial.print(c); Serial.print("*C\t"); 
  delay(250);
  tempsensor.shutdown_wake(1); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere
  int16_t adc0, adc1, adc2, adc3;
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  //Serial.print("AIN0: "); 
  Serial.println(adc0);
  //Serial.print("AIN1: "); Serial.println(adc1);

  
  delay(1000);
}

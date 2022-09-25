#include "ESP8266WiFi.h"

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(2000);
  Serial.println("Setup done");
}

void loop() {
  Serial.println("Wifi scan started");
  int n = WiFi.scanNetworks();
  Serial.println("Wifi scan ended");
  if (n == 0) 
  {
    Serial.println("no networks found");
  } 
  else 
   {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      Serial.print(i + 1);
      Serial.print(") ");
      Serial.println(WiFi.SSID(i));// SSID   
      delay(10);
    }
  }
  Serial.println("");
  delay(5000);
  WiFi.scanDelete();  
}

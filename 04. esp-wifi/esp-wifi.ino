#include<ESP8266WiFi.h>

const char* wifiName ="Redmi Note 9 Pro";
const char* pass  ="123456789";
void setup() {
      Serial.begin(9600); 
      WiFi.begin(wifiName , pass);
      while(WiFi.status() != WL_CONNECTED)
      {    Serial.print("...");
           delay(200);  
      }
      Serial.println();
      Serial.println("ESP is connnected");
      
      Serial.println( WiFi.localIP());  // my esp local IP adderess is 192.168.132.193

}

void loop() {

}


#define BLYNK_TEMPLATE_ID "TMPLSjyBjTqg"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "6H3JcNTUVsrMrNXtRP-HwAI9Qu4LNRzs"

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Redmi Note 9 Pro";
char pass[] = "123456780";

BLYNK_WRITE(V0)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 0)
  {
    digitalWrite(LED_BUILTIN,HIGH);
  }
  if(value == 1)
  {
    digitalWrite(LED_BUILTIN,LOW);
  }
}

BLYNK_WRITE(V1)
{
  
  int value = param.asInt();
  Serial.println(value);
  if(value == 0)
  {
    digitalWrite(D3,LOW);
  }
  if(value == 1)
  {
    digitalWrite(D3,HIGH);
  }
}

BLYNK_WRITE(V2)
{
  int value = param.asInt();
  Serial.println(value);
  if(value == 0)
  {
    digitalWrite(D4,LOW);
  }
  if(value == 1)
  {
    digitalWrite(D4,HIGH);
  }
}

BLYNK_WRITE(V3)
{
  
  int value = param.asInt();
  Serial.println(value);
  if(value == 0)
  {
    digitalWrite(D5,LOW);
  }
  if(value == 1)
  {
    digitalWrite(D5,HIGH);
  }
}

BLYNK_WRITE(V4)
{
  int value = param.asInt();
  Serial.println(value);
 analogWrite(D6,value);
}




void setup()
{  
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);  
}

void loop()
{
  Blynk.run();
}

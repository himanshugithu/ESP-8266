#include <Servo.h>
Servo servo;

#define BLYNK_TEMPLATE_ID "TMPLJIq0hvJM"
#define BLYNK_DEVICE_NAME "control servo"
#define BLYNK_AUTH_TOKEN "rgMUvIA75Mc5yelB0Cnz4tOce5y3ETxD"

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "honor 9lite";
char pass[] = "12345678";

BLYNK_WRITE(V0)
{
  int value = param.asInt();
  Serial.println(value);
  int s1 = map(value,0,1023,0,180);
  servo.write(s1);
  
}






void setup()
{  
  servo.attach(2);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);  
}

void loop()
{
  Blynk.run();
}
  // put your setup code here, to run once:

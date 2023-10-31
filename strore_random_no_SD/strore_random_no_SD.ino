#include <SPI.h>
#include <SD.h>

////////////////////////////////////////////
File data;
////////////////////////////////////////////
void setup() {
 
  Serial.begin(9600);
  pinMode(34,OUTPUT);
  digitalWrite(34,HIGH);
  Serial.print("SD Card init...");  
  
  Serial.println("success");
   if (!SD.begin()) {
    Serial.println("init failed..");
    while (1);
  }
  Serial.println("init ok");
}

void loop() {
  
  int number = random(0, 10); //create random number
  String stringData = (String)number; 
 
  data= SD.open("/data.txt", FILE_APPEND);
  if (data) {
    data.println(stringData); //print the data to file
    data.close();

    Serial.println(stringData);
  } else {
    Serial.println("Cannot open file");
  }
}
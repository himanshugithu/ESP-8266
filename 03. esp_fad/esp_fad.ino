void setup() {
 
  Serial.begin(9600);

}

void loop() {
   for(int i = 0; i<1023; i= i+50)
   {
    analogWrite(D5, i);
    delay(100);
    Serial.println(i);
   }

    for(int h = 1023; h>0; h= h-50)
   {
    analogWrite(D5,h);
    delay(100);   
    Serial.println(h);
   }

}

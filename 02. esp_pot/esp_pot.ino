int in;

void setup() 
 {
 pinMode(D5,OUTPUT);
 Serial.begin(9600);
}

void loop() {
  in = analogRead(A0);
  Serial.println(in);

  analogWrite(D5, in);
  delay(100);

}

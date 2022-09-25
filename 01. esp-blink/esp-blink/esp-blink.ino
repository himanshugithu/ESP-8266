#define led  D5
void setup() {
  pinMode(led, OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  

}

void loop() {
 digitalWrite(led, HIGH);
 digitalWrite(LED_BUILTIN, HIGH);
delay(1000);
 digitalWrite(led, LOW);
 digitalWrite(LED_BUILTIN,LOW);
delay(1000);

}

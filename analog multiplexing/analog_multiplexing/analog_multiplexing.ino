void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   
  int data1  = analogRead1();
  Serial.print("sensor 1 :");
  Serial.print(data1);
  Serial.print(" / ");
  delay(200);
  int data2  = analogRead2();
  Serial.print("sensor 2 :");
  Serial.println(data2);
  delay(200); 
  //  if(data1 >= 650)
  // {
  //   digitalWrite(D3, HIGH);
  // }
  // else {
  // digitalWrite(D3, LOW);
  // } 
delay(1000);

}

int analogRead1()
{
   digitalWrite(D1,HIGH);
   digitalWrite(D2,LOW);
   return analogRead(A0);
}

int analogRead2()
{
   digitalWrite(D1,LOW);
   digitalWrite(D2,HIGH);
   return analogRead(A0);
}
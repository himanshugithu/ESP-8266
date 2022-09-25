#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
pinMode(D5,OUTPUT);
pinMode(D6,OUTPUT);
pinMode(D7,OUTPUT);
pinMode(D8,OUTPUT);
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  //mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("X: ");
  Serial.println(a.acceleration.x);
  Serial.print("Y: ");
  Serial.println(a.acceleration.y);
  Serial.print("Z: ");
  Serial.println(a.acceleration.z);
  Serial.println(" ...........");
  
 if (a.acceleration.x<-3.00)
 {
   Serial.println("up"); 
   digitalWrite(D5,HIGH);
   digitalWrite(D6,LOW);
   digitalWrite(D7,LOW);
   digitalWrite(D8,LOW);
 }


else if (a.acceleration.x>3.00)
 {
   Serial.println("down"); 
    digitalWrite(D5,LOW);
   digitalWrite(D6,HIGH);
   digitalWrite(D7,LOW);
   digitalWrite(D8,LOW);
 }
 
else if (a.acceleration.y<-2.00)
 {
   Serial.println("left"); 
    digitalWrite(D5,LOW);
   digitalWrite(D6,LOW);
   digitalWrite(D7,HIGH);
   digitalWrite(D8,LOW);
 }

else if (a.acceleration.y>2.00)
 {
   Serial.println("right"); 
   digitalWrite(D5,LOW);
   digitalWrite(D6,LOW);
   digitalWrite(D7,LOW);
   digitalWrite(D8,HIGH);    
 }
else{
   digitalWrite(D5,LOW);
   digitalWrite(D6,LOW);
   digitalWrite(D7,LOW);
   digitalWrite(D8,LOW);
}
//
//
//
//
//
//
// 
//// digitalWrite(2,LOW);
  delay(100);
}

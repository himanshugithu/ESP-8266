#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <SPI.h>
#include <SD.h>

#define SDA_1 27
#define SCL_1 26

#define SDA_2 33
#define SCL_2 32
File data;
TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);

Adafruit_MPU6050 mpu1;
Adafruit_MPU6050 mpu2;
Adafruit_MPU6050 mpu3;
Adafruit_MPU6050 mpu4;


void setup() {
  Serial.begin(115200);
  pinMode(34,OUTPUT);
  digitalWrite(34,HIGH);
  Serial.print("SD Card init...");
   if (!SD.begin()) {
    Serial.println("init failed..");
    while (1);
  }
  Serial.println("init ok");
  Serial.println("//////////////////////////////////////////////////////////////////////");
  Serial.println(F("MPU506- test"));
  I2Cone.begin(SDA_1, SCL_1, 100000); 
  I2Ctwo.begin(SDA_2, SCL_2, 100000);

  bool status1 = mpu1.begin(0x68, &I2Cone);  
  if (!status1) {
    Serial.println("Could not find a valid mpu_1 sensor, check wiring!");
    while (1);
  }
  
  bool status2 = mpu2.begin(0x69, &I2Cone);  
  if (!status2) {
    Serial.println("Could not find a valid mpu_2 sensor, check wiring!");
    while (1);
  }

    bool status3 = mpu3.begin(0x68, &I2Cone);  
  if (!status3) {
    Serial.println("Could not find a valid mpu_3 sensor, check wiring!");
    while (1);
  }
  
  bool status4 = mpu4.begin(0x69, &I2Cone);  
  if (!status4) {
    Serial.println("Could not find a valid mpu_4 sensor, check wiring!");
    while (1);
  }
  Serial.println("//////////////////////////////////////////////////////////////////////");

  
  
  Serial.println("success");
  mpu1.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu1.setFilterBandwidth(MPU6050_BAND_21_HZ);
  mpu2.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu2.setFilterBandwidth(MPU6050_BAND_21_HZ);
  mpu3.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu3.setFilterBandwidth(MPU6050_BAND_21_HZ);
  mpu4.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu4.setFilterBandwidth(MPU6050_BAND_21_HZ);
}
void loop()
{
  sensors_event_t a1, g1, temp1;
  mpu1.getEvent(&a1, &g1, &temp1);
  sensors_event_t a2, g2, temp2;
  mpu2.getEvent(&a2, &g2, &temp2);
  sensors_event_t a3, g3, temp3;
  mpu2.getEvent(&a3, &g3, &temp3);
  sensors_event_t a4, g4, temp4;
  mpu2.getEvent(&a4, &g4, &temp4);

  Serial.print("X1: ");
  Serial.println(a1.acceleration.x);
  Serial.print("Y1: ");
  Serial.println(a1.acceleration.y);
  Serial.print("Z1: ");
  Serial.println(a1.acceleration.z);
  Serial.println(" .................................................................");

  Serial.print("X2: ");
  Serial.println(a2.acceleration.x);
  Serial.print("Y2: ");
  Serial.println(a2.acceleration.y);
  Serial.print("Z2: ");
  Serial.println(a2.acceleration.z);
  Serial.println(" .................................................................");
  
  String stringDataX1 = (String)a1.acceleration.x; //convert number to string
  String stringDataY1 = (String)a1.acceleration.y;
  String stringDataZ1 = (String)a1.acceleration.z;
  String stringDataX2 = (String)a2.acceleration.x; //convert number to string
  String stringDataY2 = (String)a2.acceleration.y;
  String stringDataZ2 = (String)a2.acceleration.z;
  String stringDataX3 = (String)a3.acceleration.x; //convert number to string
  String stringDataY3 = (String)a3.acceleration.y;
  String stringDataZ3 = (String)a3.acceleration.z;
  String stringDataX4 = (String)a4.acceleration.x; //convert number to string
  String stringDataY4 = (String)a4.acceleration.y;
  String stringDataZ4 = (String)a4.acceleration.z;

  data= SD.open("/data.txt", FILE_APPEND);
  if (data) {
    data.print("X1 : ");
    data.print(stringDataX1);
    data.print("\t");
    data.print("X2 : ");
    data.print(stringDataX2);
    data.print("\t");
    data.print("X3 : ");
    data.print(stringDataX3);     //print the data to file
    data.print("\t");
    data.print("X4 : ");
    data.println(stringDataX4);

    data.print("Y1 : ");
    data.print(stringDataY1);
    data.print("\t");
    data.print("Y2 : ");
    data.print(stringDataY2);
    data.print("\t");
    data.print("Y3 : ");
    data.print(stringDataY3);
    data.print("\t");
    data.print("Y4 : ");
    data.println(stringDataY4);

    data.print("Z1 : ");
    data.print(stringDataZ1);
    data.print("\t");
    data.print("Z2 : ");
    data.print(stringDataZ2); 
    data.print("\t");
    data.print("Z3 : ");
    data.print(stringDataZ3);
    data.print("\t");
    data.print("Z4 : ");
    data.println(stringDataZ4);  
    data.println(".................................................");
    data.close();

    //Serial.println(stringData);
  } else {
    Serial.println("Cannot open file");
  }
  delay(100);
}
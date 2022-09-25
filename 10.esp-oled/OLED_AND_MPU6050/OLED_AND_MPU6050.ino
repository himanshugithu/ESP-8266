#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Adafruit_MPU6050 mpu;

void setup(void) {
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  Serial.begin(115200);
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  //////////////////////////////////////////////////////////////////

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display
  oled.println("");
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

  if (a.acceleration.x < -3.00)
  {
    Serial.println("DOWN");
    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
    oled.clearDisplay();
    oled.setTextColor( WHITE);
    oled.fillRect(61, 0, 8, 50, WHITE);
    oled.fillTriangle(49, 40, 79, 40, 64, 60, WHITE);
    oled.display();
   
  }

  else if (a.acceleration.x > 3.00)
  {
    Serial.println("UP");
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);


    oled.clearDisplay();
    oled.setTextColor( WHITE);
    oled.fillRect(61, 25, 8, 60, WHITE);
    oled.fillTriangle(64, 2, 49, 25, 79, 25, WHITE);
    oled.display();
  }

  else if (a.acceleration.y < -2.00)
  {
    Serial.println("left");
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
    digitalWrite(D8, LOW);
    oled.clearDisplay();
    oled.setTextColor( WHITE);
    oled.setCursor(34, 20);
    oled.fillRect(10, 31, 60, 8, WHITE);
    oled.fillTriangle(70, 20, 70, 50, 98, 35, WHITE);
    oled.display();
    oled.startscrollright(0x00, 0x07);
    delay(100);
    oled.stopscroll();
  }

  else if (a.acceleration.y > 2.00)
  {
    Serial.println("right");
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
    digitalWrite(D8, HIGH);
    oled.clearDisplay();
    oled.setTextColor( WHITE);
    oled.setCursor(34, 20);
    oled.fillRect(40, 28, 60, 8, WHITE);
    oled.fillTriangle(18, 32, 45, 19, 45, 45, WHITE);

    oled.display();
    oled.startscrollleft(0x00, 0x07);
    delay(100);
    oled.stopscroll();

  }

  else {
    oled.clearDisplay();
    //oled.setTextColor( BLACK);
    oled.fillCircle(64, 32, 20, WHITE);
    oled.drawCircle(64, 32, 15, BLACK);

    oled.display();
    oled.stopscroll();

    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
  }


  delay(100);
}


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,4);

void setup() {
  Serial.begin(9600);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(2000);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.clearDisplay();
 oled.setTextColor(WHITE); 
oled.setCursor(0,0);
oled.setTextSize(1);
oled.println("Full");
oled.println("screen");
oled.println("scrolling");
oled.display();
oled.startscrollright(0x01, 0x05);
//delay(2000);               // show on OLED
}

void loop() {
}

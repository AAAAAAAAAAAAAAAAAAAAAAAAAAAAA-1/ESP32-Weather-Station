
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS 42
#define TFT_RST 41
#define TFT_DC 40
#define TFT_BACKLITE 45
#define TFT_I2C_POWER 7

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(115200);

  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);

  delay(10);

  tft.init(135, 240);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextSize(2);
  tft.setCursor(10, 20);
  tft.setTextColor(ST77XX_RED);
  tft.println("Temperature");

  tft.setCursor(10, 50);
  tft.setTextColor(ST77XX_GREEN);
  tft.println("Humidity");

  tft.setCursor(10, 80);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.println("UV Reading");

  tft.setCursor(10, 110);
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Display OK");

  Serial.println("Yo the display's working or sum");
}

void loop() {
  // The display remains unchanged.
}

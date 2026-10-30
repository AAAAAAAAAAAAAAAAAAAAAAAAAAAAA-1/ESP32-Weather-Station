
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_CS        42
#define TFT_RST       41
#define TFT_DC        40
#define TFT_BACKLITE  45
#define TFT_I2C_POWER 7

#define BUTTON_D0 0
#define BUTTON_D1 1
#define BUTTON_D2 2

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);

enum Screen {
  SCREEN_1,
  SCREEN_2,
  SCREEN_3
};

Screen currentScreen = SCREEN_1;

void ShowScreen1() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.setCursor(60, 50);
  tft.println("Screen 1");
}

void ShowScreen2() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.setCursor(60, 50);
  tft.println("Screen 2");
}

void ShowScreen3() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.setTextSize(3);
  tft.setCursor(60, 50);
  tft.println("Screen 3");
}

void setup() {
  Serial.begin(115200);

  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);

  pinMode(BUTTON_D0, INPUT_PULLUP);
  pinMode(BUTTON_D1, INPUT_PULLDOWN);
  pinMode(BUTTON_D2, INPUT_PULLDOWN);

  tft.init(135, 240);
  tft.setRotation(3);

  ShowScreen1();
  Serial.println("Screen switching test started.");
}

void loop() {
  if (digitalRead(BUTTON_D0) == LOW) {
    currentScreen = SCREEN_1;
    ShowScreen1();
    Serial.println("Screen 1 selected.");
    delay(250);
  }
  else if (digitalRead(BUTTON_D1) == HIGH) {
    currentScreen = SCREEN_2;
    ShowScreen2();
    Serial.println("Screen 2 selected.");
    delay(250);
  }
  else if (digitalRead(BUTTON_D2) == HIGH) {
    currentScreen = SCREEN_3;
    ShowScreen3();
    Serial.println("Screen 3 selected.");
    delay(250);
  }
}

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_LTR390.h>
#include <string>

#define TFT_CS        42
#define TFT_RST       41
#define TFT_DC        40
#define TFT_BACKLITE  45
#define TFT_I2C_POWER 7
#define BUTTON_D0     0
#define BUTTON_D1     1
#define BUTTON_D2     2
#define SDA_PIN       3
#define SCL_PIN       4


Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
Adafruit_BMP280 bmp;
Adafruit_AHTX0 aht;
Adafruit_LTR390 ltr = Adafruit_LTR390();

void CheckAHT();
void CheckLTR();

String GetWeatherMessage(float temp, float humidity, float lux) {
  if (temp > 28 && humidity > 75 && lux > 10000) {
    return "Hot and humid with strong sunshine.";
  }

  if (temp < 12 && lux < 500) {
    return "Cool and overcast conditions.";
  }

  if (lux > 15000 && humidity < 60) {
    return "Clear and sunny weather.";
  }

  return "Mild weather conditions.";
}

void CheckAHT() {
  while (true) {
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);
    int lux = ltr.readUVS();
    String message = GetWeatherMessage(temp.temperature, humidity.relative_humidity, lux);

    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0, 50);
    tft.print(message);
      if (digitalRead(BUTTON_D0) == 0){
        return;
      }
      if (digitalRead(BUTTON_D2) == 1){
        CheckLTR();
        return;
      }
    delay (100);
  }  
}

void CheckLTR() {
  while (true) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(0, 50);
    tft.setTextColor(ST77XX_MAGENTA);
    tft.setTextSize(2);
    tft.print("UV Count: ");
    tft.setCursor(120,50);
    tft.setTextColor(ST77XX_WHITE);
    tft.print((ltr.readUVS()));
      if (digitalRead(BUTTON_D0) == 0){
        return;
      }
      if (digitalRead(BUTTON_D1) == 1){
        CheckAHT();
        return;
      }
    delay (100);
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  bmp.begin();
  if (!aht.begin()) {
    Serial.println("Failed to find AHT10/AHT20 sensor!");
    while (1) delay(10); 
  }
  Serial.println("Sensor found!");
  if (!ltr.begin()) {
    Serial.println("Couldn't find LTR390 sensor! Check wiring.");
    while (1) delay(10);
  }
  
  Serial.println("Found LTR390 sensor!");
  
  ltr.setMode(LTR390_MODE_UVS);
  ltr.setGain(LTR390_GAIN_3);
  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  pinMode(13, OUTPUT);
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  pinMode(BUTTON_D0, INPUT_PULLUP);
  pinMode(BUTTON_D1, INPUT_PULLDOWN);
  pinMode(BUTTON_D2, INPUT_PULLDOWN);
  delay(10);
  tft.init(135, 240);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(2);
  tft.print("Temperature: ");
  tft.setCursor(0, 50);
  tft.setTextColor(ST77XX_WHITE);
  tft.print((temp.temperature));
  tft.setCursor(60, 50);
  tft.print("OC");
  tft.setCursor(0, 20);
  tft.setTextSize(1);
  tft.print("READINGS: ");
  tft.setCursor(0, 10);
  tft.print("Press D1 for weather conditions");
  tft.setTextSize(2);
  tft.setCursor(0, 70);
  tft.setTextColor(ST77XX_ORANGE);
  tft.print("Humidity: ");
  tft.setCursor(0, 90);
  tft.setTextColor(ST77XX_WHITE);
  tft.print((humidity.relative_humidity));
  tft.setCursor(60, 90);
  tft.print("%");
  tft.setCursor(0, 110);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.setTextSize(2);
  tft.print("UV Count: ");
  tft.setCursor(120,110);
  tft.setTextColor(ST77XX_WHITE);
  tft.print((ltr.readUVS()));
  if (digitalRead(BUTTON_D1) == 1){
  CheckAHT();
 }
if (digitalRead(BUTTON_D2) == 1){
  CheckLTR();
 }
}

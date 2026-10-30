
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_LTR390.h>

#define SDA_PIN 3
#define SCL_PIN 4

Adafruit_LTR390 ltr;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!ltr.begin()) {
    Serial.println("ERROR: LTR390 sensor not found!");
    while (true) delay(100);
  }

  ltr.setMode(LTR390_MODE_UVS);
  ltr.setGain(LTR390_GAIN_3);
  ltr.setResolution(LTR390_RESOLUTION_16BIT);

  Serial.println("LTR390 sensor connected successfully.");
}

void loop() {
  Serial.print("UV Sensor Count: ");
  Serial.println(ltr.readUVS());

  delay(1000);
}

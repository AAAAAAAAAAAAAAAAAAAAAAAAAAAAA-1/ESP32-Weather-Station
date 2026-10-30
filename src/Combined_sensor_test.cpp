
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_LTR390.h>

#define TFT_I2C_POWER 7
#define SDA_PIN 3
#define SCL_PIN 4

Adafruit_BMP280 bmp;
Adafruit_AHTX0 aht;
Adafruit_LTR390 ltr;

void setup() {
  Serial.begin(115200);

  // Enable sensor power
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);

  // Start I2C communication
  Wire.begin(SDA_PIN, SCL_PIN);

  Serial.println("WEATHER STATION SENSOR TEST");
  Serial.println("---------------------------");

  if (!aht.begin()) {
    Serial.println("ERROR: AHT20 not detected!");
    while (true) delay(100);
  }
  Serial.println("AHT20: Connected successfully.");

  if (!ltr.begin()) {
    Serial.println("ERROR: LTR390 not detected!");
    while (true) delay(100);
  }
  Serial.println("LTR390: Connected successfully.");

  ltr.setMode(LTR390_MODE_UVS);
  ltr.setGain(LTR390_GAIN_3);
  ltr.setResolution(LTR390_RESOLUTION_16BIT);

  Serial.println("---------------------------");
  Serial.println("All sensors found!");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  uint32_t uv = ltr.readUVS();

  Serial.println();
  Serial.println("SENSOR READINGS");
  Serial.println("---------------------------");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %");

  Serial.print("UV Count: ");
  Serial.println(uv);

  Serial.println("---------------------------");
  delay(2000);
}
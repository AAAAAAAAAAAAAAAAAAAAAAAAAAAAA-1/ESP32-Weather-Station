
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>

#define SDA_PIN 3
#define SCL_PIN 4

Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!aht.begin()) {
    Serial.println("ERROR: AHT20 sensor not found!");
    while (true) delay(100);
  }

  Serial.println("AHT20 sensor connected successfully.");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degrees C");

  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println("%");

  Serial.println("--------------------");
  delay(2000);
}

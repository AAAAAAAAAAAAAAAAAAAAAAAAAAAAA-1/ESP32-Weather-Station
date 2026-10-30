
#include <Arduino.h>

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

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("WEATHER MESSAGE LOGIC TEST");
  Serial.println("--------------------------");

  Serial.println("Test 1: Hot, humid and bright");
  Serial.println(GetWeatherMessage(32, 80, 12000));

  Serial.println();

  Serial.println("Test 2: Cool and low light");
  Serial.println(GetWeatherMessage(8, 70, 300));

  Serial.println();

  Serial.println("Test 3: Bright and low humidity");
  Serial.println(GetWeatherMessage(24, 45, 18000));

  Serial.println();

  Serial.println("Test 4: Default conditions");
  Serial.println(GetWeatherMessage(20, 65, 5000));
}

void loop() {
  // The tests run once in setup().
}

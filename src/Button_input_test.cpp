
#include <Arduino.h>

#define BUTTON_D0 0
#define BUTTON_D1 1
#define BUTTON_D2 2

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_D0, INPUT_PULLUP);
  pinMode(BUTTON_D1, INPUT_PULLDOWN);
  pinMode(BUTTON_D2, INPUT_PULLDOWN);

  Serial.println("Button input test started.");
  Serial.println("Press each button and watch the readings.");
}

void loop() {
  Serial.print("D0: ");
  Serial.print(digitalRead(BUTTON_D0));

  Serial.print(" | D1: ");
  Serial.print(digitalRead(BUTTON_D1));

  Serial.print(" | D2: ");
  Serial.println(digitalRead(BUTTON_D2));

  delay(200);
}

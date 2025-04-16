#include <Arduino.h>
#include <ArduinoJson.h>

const int encoderAPin = 2;
const int encoderBPin = 3;

volatile long encoderValue = 0;
volatile bool lastA = false;

void pulseAPin() {
  bool b = digitalRead(encoderBPin);
  if (!lastA && b) {
    encoderValue++;
  } else if (lastA && !b) {
    encoderValue--;
  }
  lastA = !lastA;
}

void pulseBPin() {
  bool a = digitalRead(encoderAPin);
  if (!a && lastA) {
    encoderValue++;
  } else if (a && !lastA) {
    encoderValue--;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(encoderAPin, INPUT_PULLUP);
  pinMode(encoderBPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderAPin), pulseAPin, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderBPin), pulseBPin, RISING);
}

void loop() {
  JsonDocument doc;

  doc["encoder"] = encoderValue;

  serializeJson(doc, Serial);
  Serial.println();

  delay(100);
}

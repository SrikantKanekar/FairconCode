#include "Sensor.h"

uint8_t _roomPin = D7;
uint8_t _tecPin = D8;
uint8_t _adcPin = A0;

float reading;
float temperature;

void Sensor::init() {
    pinMode(_roomPin, OUTPUT);
    digitalWrite(_roomPin, LOW);
    pinMode(_tecPin, OUTPUT);
    digitalWrite(_tecPin, LOW);
    Serial.println("Sensor         --> Sensor Class Initialized");
}

float Sensor::roomValue() {
    digitalWrite(_roomPin, HIGH);
    digitalWrite(_tecPin, LOW);
    reading = analogRead(_adcPin);
    temperature = (reading * 500) / 1023;
    return temperature;
}

float Sensor::tecValue() {
    digitalWrite(_roomPin, LOW);
    digitalWrite(_tecPin, HIGH);
    reading = analogRead(_adcPin);
    temperature = (reading * 500) / 1023;
    return temperature;
}
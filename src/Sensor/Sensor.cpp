#include "Sensor.h"

uint8_t _roomPin = D3;
uint8_t _tecPin = D4;
uint8_t _adcPin = A0;

float reading;
float temperature;

void printRoomTemp();
void printTecTemp();

void Sensor::init() {
    pinMode(_roomPin, OUTPUT);
    pinMode(_tecPin, OUTPUT);
}

float Sensor::roomValue() {
    digitalWrite(_roomPin, HIGH);
    digitalWrite(_tecPin, LOW);
    reading = analogRead(_adcPin);
    temperature = (reading * 500) / 1023;
    printRoomTemp();
    return temperature;
}

float Sensor::tecValue() {
    digitalWrite(_roomPin, LOW);
    digitalWrite(_tecPin, HIGH);
    reading = analogRead(_adcPin);
    temperature = (reading * 500) / 1023;
    printTecTemp();
    return temperature;
}

void printRoomTemp() {
    Serial.print("Room temperature value = ");
    Serial.println(temperature);
}

void printTecTemp() {
    Serial.print("Tec temperature value = ");
    Serial.println(temperature);
}

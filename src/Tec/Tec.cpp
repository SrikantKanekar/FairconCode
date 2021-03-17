#include "Tec.h"

uint8_t _tecPin = D0;
uint8_t _spdtPin = D1;
uint8_t _dpdtPin = D2;
float _voltage = 0;

void printVoltage();
void updateVoltage();

void Tec::init() {
    pinMode(_spdtPin, OUTPUT);
    digitalWrite(_spdtPin, LOW);

    pinMode(_dpdtPin, OUTPUT);
    digitalWrite(_dpdtPin, LOW);

    updateVoltage();
}

void Tec::start() {
    digitalWrite(_spdtPin, HIGH);
}

void Tec::setVoltage(float voltage) {
    _voltage = voltage;
    updateVoltage();
}

/*
 Voltage   dutyCycle
   12V        255
    0V         0
    x          y
  y/255 = x/12
      y = 255 * x / 12 
*/
void updateVoltage() {
    uint16_t dutyCycle = 255 * _voltage / 12;  //Above equation
    if (dutyCycle > 255) {
        dutyCycle = 255;
    } else if (dutyCycle < 0) {
        dutyCycle = 0;
    }
    analogWrite(_tecPin, dutyCycle);
    printVoltage();
}

void Tec::cool() {
    digitalWrite(_dpdtPin, LOW);
}

void Tec::heat() {
    digitalWrite(_dpdtPin, HIGH);
}

void Tec::faster() {
    _voltage = _voltage + 2;
    updateVoltage();
}

void Tec::slower() {
    _voltage = _voltage - 2;
    updateVoltage();
}

bool Tec::isRunning() {
    return digitalRead(_spdtPin) == HIGH;
}

bool Tec::isNotRunning() {
    return digitalRead(_spdtPin) == LOW;
}

bool Tec::isCooling() {
    return digitalRead(_dpdtPin) == LOW;
}

bool Tec::isHeating() {
    return digitalRead(_dpdtPin) == HIGH;
}

void Tec::stop() {
    digitalWrite(_spdtPin, LOW);
}

void printVoltage() {
    Serial.print("Tec voltage : ");
    Serial.println(_voltage);
}

#include "Tec.h"

uint8_t _spdtPin = D0;
uint8_t _dpdtPin = D1;
uint8_t _TecPin = D5;
float _voltage = 0;

void printVoltage();
void updateVoltage();

void Tec::init() {
    pinMode(_spdtPin, OUTPUT);
    digitalWrite(_spdtPin, LOW);

    pinMode(_dpdtPin, OUTPUT);
    digitalWrite(_dpdtPin, LOW);
    Serial.println("Tec            --> Tec Class Initialized");
}

void Tec::start() {
    digitalWrite(_spdtPin, HIGH);
    Serial.println("Tec            --> Tec Started");
}

void Tec::setVoltage(float voltage) {
    _voltage = voltage;
    updateVoltage();
}

float Tec::getVoltage() {
    return _voltage;
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
    analogWrite(_TecPin, dutyCycle);
    printVoltage();
}

void Tec::cool() {
    digitalWrite(_dpdtPin, LOW);
    Serial.println("Tec            --> Tec Cooling Started");
}

void Tec::heat() {
    digitalWrite(_dpdtPin, HIGH);
    Serial.println("Tec            --> Tec Heating Started");
}

void Tec::faster() {
    _voltage = _voltage + 2;
    if (_voltage > 12) {
        _voltage = 12;
    }
    updateVoltage();
}

void Tec::slower() {
    _voltage = _voltage - 2;
    if (_voltage < 0) {
        _voltage = 0;
    }
    updateVoltage();
}

bool Tec::isTecRunning() {
    return digitalRead(_spdtPin) == HIGH;
}

void Tec::stop() {
    digitalWrite(_spdtPin, LOW);
    Serial.println("Tec            --> Tec Stopped");
}

void printVoltage() {
    Serial.print("Tec            --> Tec voltage updated : ");
    Serial.println(_voltage);
}

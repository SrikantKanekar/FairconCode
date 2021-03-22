#include "Fan.h"

uint8_t _relayPin = D2;
uint8_t _fanPin = D6;
uint16_t _speed = 300;

void printSpeed();
void updateSpeed();

void Fan::init() {
    pinMode(_relayPin, OUTPUT);
    digitalWrite(_relayPin, LOW);
    Serial.println("Fan            --> Fan Class Initialized");
}

void Fan::start() {
    digitalWrite(_relayPin, HIGH);
    Serial.println("Fan            --> Fan Started");
}

void Fan::setSpeed(uint16_t speed) {
    _speed = speed;
    updateSpeed();
}

uint16_t Fan::getSpeed() {
    return _speed;
}

/*
  speed   dutyCycle
  300rpm     150
  400rpm     250
    x         y
 (y - 250)/100 = (x - 400)/100
             y = x - 150 
*/
void updateSpeed() {
    uint16_t dutyCycle = _speed - 150;  //Above equation
    if (dutyCycle > 255) {
        dutyCycle = 255;
    } else if (dutyCycle < 0) {
        dutyCycle = 0;
    }
    analogWrite(_fanPin, dutyCycle);
    printSpeed();
}

void Fan::faster() {
    _speed = _speed + 20;
    if (_speed > 400) {
        _speed = 400;
    }
    updateSpeed();
}

void Fan::slower() {
    _speed = _speed - 20;
    if (_speed < 300) {
        _speed = 300;
    }
    updateSpeed();
}

void Fan::stop() {
    digitalWrite(_relayPin, LOW);
    Serial.println("Fan            --> Fan Stopped");
}

void printSpeed() {
    Serial.print("Fan            --> Fan Speed updated : ");
    Serial.print(_speed);
    Serial.println(" RPM");
}
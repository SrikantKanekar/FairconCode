#include "Fan.h"

uint8_t _fanPin = D0;
uint8_t _relayPin = D1;
uint16_t _speed = 300;

void printSpeed()
{
    Serial.print("Fan Speed :");
    Serial.println(_speed);
}

/*
  speed   dutyCycle
  300rpm     150
  400rpm     250
    x         y
 (y - 250)/100 = (x - 400)/100
             y = x - 150 
*/
void updateSpeed()
{
    uint16_t dutyCycle = _speed - 150;
    if (dutyCycle > 255)
    {
        dutyCycle = 255;
    }
    else if (dutyCycle < 0)
    {
        dutyCycle = 0;
    }
    analogWrite(_fanPin, dutyCycle);
    printSpeed();
}

void Fan::init()
{
    pinMode(_relayPin, OUTPUT);
    digitalWrite(_relayPin, LOW);
    updateSpeed();
}

void Fan::start()
{
    digitalWrite(_relayPin, HIGH);
}

void Fan::setSpeed(uint16_t speed)
{
    _speed = speed;
    updateSpeed();
}

bool Fan::isRunning(){
    return digitalRead(_relayPin) == HIGH;
}

void Fan::stop()
{
    digitalWrite(_relayPin, LOW);
}
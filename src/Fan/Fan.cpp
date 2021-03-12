#include "Fan.h"

uint8_t _pin;
uint16_t _speed;

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
   y - 250 = x - 400
    100       100
   y = x - 150 
*/
void updateSpeed()
{
    uint16_t dutyCycle = _speed - 150; // Above equation
    if (dutyCycle > 255){
        dutyCycle = 255;
    }else if (dutyCycle < 0)
    {
        dutyCycle = 0;
    }
    analogWrite(_pin, dutyCycle);
    printSpeed();
}

Fan::Fan(uint8_t pin, uint16_t initialSpeed)
{
    _pin = pin;
    _speed = initialSpeed;
    updateSpeed();
}

void Fan::setSpeed(uint16_t speed)
{
    _speed = speed;
    updateSpeed();
}
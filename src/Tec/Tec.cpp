#include "Tec.h"

uint8_t _tecPin;
float _voltage;

void printVoltage()
{
    Serial.print("Tec voltage : ");
    Serial.println(_voltage);
}

/*
 voltage   dutyCycle
  12V        255
   0V         0
   x          y
   y  =  x
  255   12
   y = 255 * x / 12 
*/
void updateVoltage()
{
    uint16_t dutyCycle = 255 * _voltage / 12; // Above equation
    if (dutyCycle > 255){
        dutyCycle = 255;
    }else if (dutyCycle < 0)
    {
        dutyCycle = 0;
    }
    analogWrite(_tecPin, dutyCycle);
    printVoltage();
}

Tec::Tec(uint8_t pin, float initialVoltage)
{
    _tecPin = pin;
    _voltage = initialVoltage;
    updateVoltage();
}

void Tec::setVoltage(float voltage)
{
    _voltage = voltage;
    updateVoltage();
}
#include "LM35.h"

float temperature;
float reading;

void printTemperature()
{
    Serial.print("LM35 temperature value = ");
    Serial.println(temperature);
}

LM35::LM35(int pin)
{
    _pin = pin;
    pinMode(_pin, INPUT);
}

float LM35::value()
{
    reading = analogRead(_pin);
    temperature = (reading * 500) / 1023;
    printTemperature();
    return temperature;
}
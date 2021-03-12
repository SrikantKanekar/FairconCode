#ifndef TEC_h
#define TEC_h

#include <Arduino.h>

class Tec
{
public:
    Tec(uint8_t pin, float initialVoltage);
    void setVoltage(float voltage);
};

#endif
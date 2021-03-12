#ifndef FAN_h
#define FAN_h

#include <Arduino.h>

class Fan
{
public:
    Fan(uint8_t pin, uint16_t initialSpeed);
    void setSpeed(uint16_t speed);
};

#endif
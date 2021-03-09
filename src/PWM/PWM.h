#ifndef PWM_h
#define PWM_h

#include <Arduino.h>

class PWM
{
public:
    PWM(uint8_t pin, uint16_t dutyCycle);
    void dutyCycle(uint16_t dutyCycle);
};

#endif
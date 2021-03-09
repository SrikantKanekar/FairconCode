#include "PWM.h"

uint8_t _pin;
uint16_t _dutycycle;

void printDutyCycle()
{
    Serial.print("Duty Cycle updated : ");
    Serial.println(_dutycycle);
}

void updateDutyCycle()
{
    if (_dutycycle > 1023)
        _dutycycle = 1023;
    analogWrite(_pin, _dutycycle);
    printDutyCycle();
}

PWM::PWM(uint8_t pin, uint16_t dutyCycle)
{
    _pin = pin;
    _dutycycle = dutyCycle;
    updateDutyCycle();
}

void PWM::dutyCycle(uint16_t dutyCycle)
{
    _dutycycle = dutyCycle;
    updateDutyCycle();
}
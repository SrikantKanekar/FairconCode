#include "Function.h"

Faircon *current;
Faircon *old;

Function::Function(Faircon *Current, Faircon *Old)
{
    current = current;
    old = Old;
}

bool Function::hasControllerChanged()
{
    return (*current).controller.fanSpeed != (*old).controller.fanSpeed ||
           (*current).controller.temperature != (*old).controller.temperature ||
           (*current).controller.tecVoltage != (*old).controller.tecVoltage;
}

bool Function::hasControllerFanSpeedChanged()
{
    return (*current).controller.fanSpeed != (*old).controller.fanSpeed;
}

bool Function::hasControllerTempChanged()
{
    return (*current).controller.temperature != (*old).controller.temperature;
}

bool Function::hasControllerVoltageChanged()
{
    return (*current).controller.tecVoltage != (*old).controller.tecVoltage;
}

bool Function::hasModeChanged()
{
    return (*current).mode != (*old).mode;
}
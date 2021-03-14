#include "Function.h"

bool Function::hasControllerChanged(Faircon current, Faircon old)
{
    return current.controller.fanSpeed != old.controller.fanSpeed ||
           current.controller.temperature != old.controller.temperature ||
           current.controller.tecVoltage != old.controller.tecVoltage;
}

bool Function::hasModeChanged(Faircon current, Faircon old)
{
    return current.mode != old.mode;
}
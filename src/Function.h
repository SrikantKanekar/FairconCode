#ifndef FUNCTION_h
#define FUNCTION_h

#include "Arduino.h"
#include "Structure.h"

class Function
{
public:
    bool hasControllerChanged(Faircon current, Faircon old);
    bool hasModeChanged(Faircon current, Faircon old);
};

#endif
#ifndef FUNCTION_h
#define FUNCTION_h

#include "Arduino.h"
#include "Structure.h"

class Function {
   public:
    Function(Faircon *Current, Faircon *Old);
    bool hasControllerChanged();
    bool hasControllerFanSpeedChanged();
    bool hasControllerTempChanged();
    bool hasControllerVoltageChanged();
    bool hasModeChanged();
};

#endif
#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"

class Sensor {
   public:
    void init();
    float roomValue();
    float tecValue();
};

#endif
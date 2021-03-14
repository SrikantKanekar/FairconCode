#ifndef FAN_h
#define FAN_h

#include "Arduino.h"

class Fan
{
public:
    void init();
    void start();
    void setSpeed(uint16_t speed);
    void stop();
};

#endif
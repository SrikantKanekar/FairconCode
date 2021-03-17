#ifndef TEC_h
#define TEC_h

#include "Arduino.h"

class Tec {
   public:
    void init();
    void start();
    void setVoltage(float voltage);
    void cool();
    void heat();
    void faster();
    void slower();
    bool isRunning();
    bool isNotRunning();
    bool isCooling();
    bool isHeating();
    void stop();
};

#endif
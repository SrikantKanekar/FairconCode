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
    bool isRunning();
    bool isCooling();
    void faster();
    void slower();
    void stop();
};

#endif
#ifndef LM35_h
#define LM35_h

#include "Arduino.h"

class LM35 {
   private:
    int _pin;

   public:
    LM35(int pin);
    float value();
};

#endif
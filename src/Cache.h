#ifndef Cache_h
#define Cache_h

#include "Arduino.h"
#include "EEPROM.h"
#include "Data.h"

class Cache {
   public:
    Cache(Faircon *Faircon);
    void init();
    void save();
};

#endif
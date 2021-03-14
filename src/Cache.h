#ifndef Cache_h
#define Cache_h

#include "Arduino.h"
#include "EEPROM.h"
#include "Structure.h"

class Cache
{
public: 
    Cache(Faircon *Faircon);
    void save();
};

#endif
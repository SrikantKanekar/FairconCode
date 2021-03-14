#include "Cache.h"

Faircon *data;

void printData();

Cache::Cache(Faircon *Faircon)
{
    data = Faircon;

    EEPROM.begin(30);
    EEPROM.get(0, *data);

    Serial.begin(115200);
    Serial.println("FAIRCON data initialised");
    printData();
}

void Cache::commit()
{
    EEPROM.put(0, *data);
    EEPROM.commit();
    Serial.println("FAIRCON Data Commited");
    printData();
}

void printData()
{
    Serial.println("");
    Serial.println("Home");
    Serial.print("Fan Speed : ");
    Serial.println((*data).home.fanSpeed);
    Serial.print("Temperature : ");
    Serial.println((*data).home.temperature);
    Serial.print("Tec Voltage : ");
    Serial.println((*data).home.tecVoltage);

    Serial.println("");
    Serial.println("Controller");
    Serial.print("Fan Speed : ");
    Serial.println((*data).controller.fanSpeed);
    Serial.print("Temperature : ");
    Serial.println((*data).controller.temperature);
    Serial.print("Tec Voltage : ");
    Serial.println((*data).controller.tecVoltage);

    Serial.println("");
    Serial.print("Mode : ");
    Serial.println((*data).mode);

    Serial.println("");
    Serial.print("Total Data Size : ");
    Serial.println(sizeof((*data)));
}

bool isDataEqual(Faircon current, Faircon stored)
{
    return current.home.fanSpeed == stored.home.fanSpeed &&
           current.home.temperature == stored.home.temperature &&
           current.home.tecVoltage == stored.home.tecVoltage &&
           current.controller.fanSpeed == stored.controller.fanSpeed &&
           current.controller.temperature == stored.controller.temperature &&
           current.controller.tecVoltage == stored.controller.tecVoltage &&
           current.mode == stored.mode;
}

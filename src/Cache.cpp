#include "Cache.h"

Faircon *data;
Controller storedData;

void printData();

Cache::Cache(Faircon *Faircon)
{
    data = Faircon;

    EEPROM.begin(30);
    EEPROM.get(0, (*data).controller);

    storedData = (*data).controller;

    Serial.begin(115200);
    Serial.println("FAIRCON data initialised");
    printData();
}

bool isDataEqual()
{
    return (*data).controller.fanSpeed == storedData.fanSpeed &&
           (*data).controller.temperature == storedData.temperature &&
           (*data).controller.tecVoltage == storedData.tecVoltage;
}

void Cache::save()
{
    if (isDataEqual())
    {
        EEPROM.put(0, (*data).controller);
        EEPROM.commit();
        storedData = (*data).controller;
        Serial.println("FAIRCON Data Saved");
        printData();
    }
    else
    {
        Serial.println("Data is same. Not commited");
    }
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
    Serial.println(sizeof(storedData));
}
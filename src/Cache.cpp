#include "Cache.h"

Faircon *data;
Controller storedData;

void initializeData();
bool isDataEqual();
void printData();

Cache::Cache(Faircon *Faircon) {
    data = Faircon;
}

void Cache::init() {
    EEPROM.begin(20);
    EEPROM.get(0, storedData);

    if (storedData.fanSpeed == 65535) {
        initializeData();
    } else {
        (*data).controller = storedData;
    }

    Serial.print("Cache          --> Cache Class Initialized");
    printData();
}

//Data is null, initializing Cache
void initializeData() {
    EEPROM.put(0, (*data).controller);
    EEPROM.commit();
    storedData = (*data).controller;
    Serial.println("Cache          --> Cache Initialized for the first time");
}

// Cache will be updated only if data is changed.
void Cache::save() {
    if (!isDataEqual()) {
        EEPROM.put(0, (*data).controller);
        EEPROM.commit();
        storedData = (*data).controller;
        Serial.print("Cache          --> Cache Updated");
        printData();
    } else {
        Serial.println("Cache          --> Cache not updated, data is Same");
    }
}

bool isDataEqual() {
    return (*data).controller.fanSpeed == storedData.fanSpeed &&
           (*data).controller.temperature == storedData.temperature &&
           (*data).controller.tecVoltage == storedData.tecVoltage;
}

void printData() {
    Serial.print(", FanSpeed: ");
    Serial.print((*data).controller.fanSpeed);
    Serial.print(", Temperature: ");
    Serial.print((*data).controller.temperature);
    Serial.print(", TecVoltage: ");
    Serial.print((*data).controller.tecVoltage);
    Serial.print(", Cache Size: ");
    Serial.println(sizeof(storedData));
}
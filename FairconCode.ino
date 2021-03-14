#include "src/Structure.h"
#include "src/WiFiConnect/WiFiConnectAP.h"
#include "src/RestApiServer.h"
#include "src/Cache.h"
#include "src/LM35/LM35.h"
#include "src/Tec/Tec.h"
#include "src/Fan/Fan.h"

Faircon Faircon;
WiFiConnectAP wiFi;
Cache cache(&Faircon);
RestApiServer server(&Faircon);
LM35 roomTemperature(D1);
LM35 tecTemperature(D2);
Tec tec;
Fan fan;

void setup(void)
{
    Serial.begin(115200);
    wiFi.start();
    fan.init();
    tec.init();
}

void checkRoomYemperature()
{
    float requiredTemp = Faircon.controller.temperature;
    float roomTemp = roomTemperature.value();

    if (roomTemp < requiredTemp)
    {
    }
    else if (roomTemp > requiredTemp)
    {
    }
}

void handelModeChange()
{
    if (Faircon.mode == IDLE)
    {
        Serial.println("Started Idle mode");
        // cache.commit();
    }
    else if (Faircon.mode == FAN)
    {
        Serial.println("Started Fan mode");
    }
    else if (Faircon.mode == COOLING)
    {
        Serial.println("Started cooling");
    }
    else if (Faircon.mode == HEATING)
    {
        Serial.println("Started Heating");
    }
}

void handleFAIRCON()
{
    // Faircon = server.getData();

    checkRoomYemperature();
    tecTemperature.value();

    fan.setSpeed(325);
    tec.setVoltage(8.5);
}

unsigned long previousMillis = 0;
const long interval = 5000;

void loop(void)
{
    server.handleClient();

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval)
    {
        previousMillis = currentMillis;
        handleFAIRCON();
    }
}
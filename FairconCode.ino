#include "src/Structure.h"
#include "src/WiFiConnect/WiFiConnectAP.h"
#include "src/RestApiServer.h"
#include "src/Cache.h"
#include "src/Function.h"
#include "src/LM35/LM35.h"
#include "src/Tec/Tec.h"
#include "src/Fan/Fan.h"

Faircon faircon;
Faircon previousData;
WiFiConnectAP wiFi;
Function func;
Cache cache(&faircon);
RestApiServer server(&faircon);
LM35 roomTemp(D1);
LM35 tecTemp(D2);
Tec tec;
Fan fan;

void setup(void)
{
    Serial.begin(115200);
    wiFi.start();
    fan.init();
    tec.init();
}

void checkRoomTemperature()
{
    float required = faircon.controller.temperature;
    float current = roomTemp.value();

    if (current < required)
    {
    }
    else if (current > required)
    {
    }
}

void handelModeChange()
{
    if (faircon.mode == IDLE)
    {
        Serial.println("Started Idle mode");
        //turn off fan and tec if its alredy on.
        //save data to cache.

        //cache.save();
    }
    else if (faircon.mode == FAN)
    {
        Serial.println("Started Fan mode");
        // turn off tec.
        // turn on fan.
    }
    else if (faircon.mode == COOLING)
    {
        Serial.println("Started cooling");
        // turn on tec and motor.
        // set tec polarity to cooling.
        // use PID for temperature control
        // for decreasing temp, increase fan speed and tec voltage.
        // for increasing temp, decrease fan speed and tec voltage.
        // handle overheating.
        // if overheating, increase fan speed and decrease tec voltage
    }
    else if (faircon.mode == HEATING)
    {
        Serial.println("Started Heating");
        //turn on tec and motor.
        //reverse tec polarity to heating.
    }
}

void handelControllerChange()
{

}

void handleFaircon()
{
    if (func.hasModeChanged(faircon, previousData))
    {
        handelModeChange();
    }
    if (func.hasControllerChanged(faircon, previousData))
    {
        handelControllerChange();
    }
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
        handleFaircon();
        previousData = faircon;
    }
}
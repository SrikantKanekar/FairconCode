#include "src/Structure.h"
#include "src/WiFiConnect/WiFiConnectAP.h"
#include "src/RestApiServer.h"
#include "src/Cache.h"
#include "src/Function.h"
#include "src/LM35/LM35.h"
#include "src/Tec/Tec.h"
#include "src/Fan/Fan.h"

Faircon faircon;
WiFiConnectAP wiFi;
Cache cache(&faircon);
Faircon previousData = faircon;
RestApiServer server(&faircon);
Function func(&faircon, &previousData);
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

void handelModeChange()
{
    if (faircon.mode == IDLE)
    {
        Serial.println("Started Idle mode");
        if (fan.isRunning() || tec.isRunning())
        {
            fan.stop();
            tec.stop();
        }
        cache.save();
    }
    else if (faircon.mode == FAN)
    {
        Serial.println("Started Fan mode");
        if (tec.isRunning())
        {
            tec.stop();
        }
        if (!fan.isRunning())
        {
            fan.start();
        }
    }
    else if (faircon.mode == COOLING)
    {
        Serial.println("Started cooling");
        if (!fan.isRunning() || !tec.isRunning())
        {
            fan.start();
            tec.start();
        }
        if (!tec.isCooling())
        {
            tec.cool();
        }
        // use PID for temperature control
        // for decreasing temp, increase fan speed and tec voltage.
        // for increasing temp, decrease fan speed and tec voltage.
        // handle overheating.
        // if overheating, increase fan speed and decrease tec voltage
    }
    else if (faircon.mode == HEATING)
    {
        Serial.println("Started Heating");
        if (!fan.isRunning() || !tec.isRunning())
        {
            fan.start();
            tec.start();
        }
        if (tec.isCooling())
        {
            tec.heat();
        }
    }
}

void handelControllerChange()
{
    if (func.hasControllerFanSpeedChanged())
    {
        fan.setSpeed(faircon.controller.fanSpeed);
    }
    if (func.hasControllerTempChanged())
    {
    }
    if (func.hasControllerVoltageChanged())
    {
        tec.setVoltage(faircon.controller.tecVoltage);
    }
}

void handlePID()
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

void handleOverHeating()
{
    if (faircon.mode == COOLING)
    {
        float temp = tecTemp.value();
        if (temp > 80)
        {
            tec.stop();
        }
        else if (temp > 70)
        {
            tec.stop();
        }
    }
}

void handleFaircon()
{
    if (func.hasModeChanged())
    {
        handelModeChange();
    }
    if (func.hasControllerChanged())
    {
        handelControllerChange();
    }
    handlePID();
    handleOverHeating();
}

unsigned long previousMillis = 0;
const long interval = 10000;
void loop(void)
{
    server.handleClient();
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval)
    {
        handleFaircon();
        previousData = faircon;
        previousMillis = currentMillis;
    }
}
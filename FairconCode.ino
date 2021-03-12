#include "src/Structure.h"
#include "src/WiFiConnect/WiFiConnectAP.h"
#include "src/RestApiServer.h"
#include "src/LM35/LM35.h"
#include "src/Tec/Tec.h"
#include "src/Fan/Fan.h"

Structure Data;
WiFiConnectAP wiFi;
RestApiServer server;
LM35 roomTemperature(D1);
LM35 tecTemperature(D2);
Tec tec(D3, 0);
Fan fan(D4, 0);

void setup(void)
{
    Serial.begin(115200);
    wiFi.start();
    server.init();
    Data = server.getData();
}

void handleFAIRCON(){
    Data = server.getData();

    roomTemperature.value();
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
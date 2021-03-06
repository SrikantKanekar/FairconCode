#include "src/RestApi/RestApiServer.h"
#include "src/WiFiConnect/WiFiConnectAP.h"

WiFiConnectAP myWiFi;
RestApiServer Server;
Data Data;

void setup(void)
{
    Serial.begin(115200);
    myWiFi.start();
    Server.init();
    Data = Server.getData();
    Server.printData(Data);
}

unsigned long previousMillis = 0;
const long interval = 5000;

void loop(void)
{
    Server.handleClient();

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval)
    {
        previousMillis = currentMillis;
        Server.set_HOME_Parameters(
            Server.get_CONTROLLER_FanSpeed(),
            Server.get_CONTROLLER_Temperature(),
            Server.get_CONTROLLER_TecVoltage());
    }
}

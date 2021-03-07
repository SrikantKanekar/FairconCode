/*
 * RestApiServer - Library which provides rest endpoints for parameter values.
 * Call Constructor above setup function and pass motor speed, temp, voltage respectively.
 * call handleClient in loop function.
 */

#ifndef RestApiServer_h
#define RestApiServer_h

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "Cache.h"
#include "Structure.h"

class RestApiServer
{
public:
    void init();
    void handleClient();
    Structure getData();

    void set_HOME_Parameters(uint16_t fanSpeed, float temperature, float tecVoltage);
    
    uint16_t get_CONTROLLER_FanSpeed();
    float get_CONTROLLER_Temperature();
    float get_CONTROLLER_TecVoltage();
};

#endif
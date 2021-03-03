/*
 * RestApiServer - Library which provides rest endpoints for parameter values.
 * Call Constructor above setup function and pass motor speed, temp, voltage respectively.
 * call handleClient in loop function.
 */

#ifndef RestApiServer_h
#define RestApiServer_h

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

class RestApiServer
{
public:
    RestApiServer(float motorSpeed, float temperature, float voltage);
    void setParameters(float motorSpeed, float temperature, float voltage);
    float getMotorSpeed();
    float getTemperature();
    float getVoltage();
    void handleClient();
};

#endif
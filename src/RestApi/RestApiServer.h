/*
 * RestApiServer - Library which provides rest endpoints for parameter values.
 * Call Constructor above setup function and pass motor speed, temp, voltage respectively.
 * call handleClient in loop function.
 */

#ifndef RestApiServer_h
#define RestApiServer_h

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

struct Home
{
    uint16_t fanSpeed = 350;
    float temperature = 25;
    float tecVoltage = 12;
};
struct Controller
{
    uint16_t fanSpeed = 350;
    float temperature = 25;
    float tecVoltage = 12;
};
enum Mode
{
    ON,
    FAN,
    COOLING,
    HEATING
};

struct Data
{
    Home home;
    Controller controller;
    Mode mode = ON;
};


class RestApiServer
{
public:
    void init();
    void handleClient();
    void commit();
    void printData(Data currentData);
    Data getData();

    void set_HOME_Parameters(uint16_t fanSpeed, float temperature, float tecVoltage);
    
    uint16_t get_CONTROLLER_FanSpeed();
    float get_CONTROLLER_Temperature();
    float get_CONTROLLER_TecVoltage();
};

#endif
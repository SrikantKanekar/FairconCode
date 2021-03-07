#ifndef Structure_h
#define Structure_h

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

struct Structure
{
    Home home;
    Controller controller;
    Mode mode = ON;
};

#endif
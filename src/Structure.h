#ifndef Structure_h
#define Structure_h

struct Home
{
    uint16_t fanSpeed = 300;
    float temperature = 15;
    float tecVoltage = 0;
};
struct Controller
{
    uint16_t fanSpeed = 300;
    float temperature = 25;
    float tecVoltage = 0;
};
enum Mode
{
    IDLE,
    FAN,
    COOLING,
    HEATING
};

enum Status
{
    STABLE,
    TRANSITION,
    OVERHEATING
};

struct Faircon
{
    Home home;
    Controller controller;
    Mode mode = IDLE;
    Status status = STABLE;
};

#endif
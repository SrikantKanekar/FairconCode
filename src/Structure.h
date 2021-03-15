#ifndef Structure_h
#define Structure_h

// Home Parameters displays the current state of the FAIRCON.
// Values are obtained from sensors and NodeMcu, and are displayed to user in real time.
struct Home {
    uint16_t fanSpeed = 300;
    float temperature = 15;
    float tecVoltage = 0;
};

// Controller is the object configured by the user, which will make FAIRCON run appropriately
// in different modes as required by the user.
// This object is stored in cache to restore previously configured settings to give better user experience.
struct Controller {
    uint16_t fanSpeed = 300;
    float temperature = 25;
    float tecVoltage = 0;
};

// IDLE    -> Only NodeMcu is ON. It contineously listenes for possible Mode change from the user.
// FAN     -> FAIRCON operates as normal ceiling fan.
// COOLING -> Tec and Fan is turned ON.
// HEATING -> Tec polarity is interchanged.
enum Mode {
    IDLE,
    FAN,
    COOLING,
    HEATING
};

// STABLE      ->  FAIRCON is operating at temp and fanSpeed set by user.
// TRANSITION  ->  FAIRCON is trying to change the roomTemp to the temp set by the user.
// OVERHEATING ->  TecTemp has excedded the max safe limit.
enum Status {
    STABLE,
    TRANSITION,
    OVERHEATING
};

struct Faircon {
    Home home;
    Controller controller;
    Mode mode = IDLE;
    Status status = STABLE;
};

#endif
#ifndef Data_h
#define Data_h

// Values obtained from Sensors and Microcontroller, and displayed to the users in real time.
struct Home {
    uint16_t fanSpeed = 300;
    float temperature = 15;
    float tecVoltage = 0;
};

// Controller is the object which can be configured by the user.
// It will make FAIRCON run appropriately in different modes, according to the users needs.
// This object is stored in cache, and will be restore during device startup to give better user experience.
struct Controller {
    uint16_t fanSpeed = 300;
    float temperature = 25;
    float tecVoltage = 0;
};

// IDLE    -> Only Microcontroller is ON. It is continuously listening for Mode change from the user.
// FAN     -> FAIRCON operates as normal ceiling fan. Tec will be turned off.
// COOLING -> Tec and Fan is turned ON.
// HEATING -> Tec and Fan is turned ON. Tec polarity is reversed.
enum Mode {
    IDLE,
    FAN,
    COOLING,
    HEATING
};

// STABLE      ->  FAIRCON is operating at temp and fanSpeed set by user.
// TRANSITION_DEC  ->  FAIRCON is trying to decrease the roomTemp to the temp set by the user.
// TRANSITION_INC  ->  FAIRCON is trying to increase the roomTemp to the temp set by the user.
// TEC_HEATING ->  TecTemp is about to reach max safe limit.
// TEC_OVERHEATING ->  TecTemp has excedded the max safe limit.
enum Status {
    STABLE,
    TRANSITION_DEC,
    TRANSITION_INC,
    TEC_HEATING,
    TEC_OVERHEATING
};

// Object containing all the data fields.
struct Faircon {
    Home home;
    Controller controller;
    Mode mode = IDLE;
    Status status = STABLE;
};

#endif
#include "src/Cache.h"
#include "src/Fan/Fan.h"
#include "src/Function.h"
#include "src/LM35/LM35.h"
#include "src/RestApiServer.h"
#include "src/Structure.h"
#include "src/Tec/Tec.h"
#include "src/WiFiConnect/WiFiConnectAP.h"

// Function definations
void handleFaircon();
void handelModeChange();
void handelControllerChange();
void handlePID();
void handleOverHeating();

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
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
const long interval = 10000;

void setup(void) {
    wiFi.start();
    fan.init();
    tec.init();
}

// handleFaircon() is executed with some delay to reduce the load on the cpu.
void loop(void) {
    server.handleClient();

    currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
        handleFaircon();
        previousData = faircon;
        previousMillis = currentMillis;
    }
}

// This function is executed every 10 seconds(will be reduced in future).
void handleFaircon() {
    if (func.hasModeChanged()) {
        handelModeChange();
    }
    if (func.hasControllerChanged()) {
        handelControllerChange();
    }

    checkState();
    handleStableState();
    handleOverHeating();
    handleTempTransition();
}

// Executed everytime user changes the Mode.
void handelModeChange() {
    Serial.print("FAIRCON Mode Changed : ");

    if (faircon.mode == IDLE) {
        Serial.println("IDLE");
        if (fan.isRunning() || tec.isRunning()) {
            fan.stop();
            tec.stop();
        }
    } else if (faircon.mode == FAN) {
        Serial.println("FAN");
        if (tec.isRunning()) {
            tec.stop();
        }
        if (fan.isNotRunning()) {
            fan.start();
        }
    } else if (faircon.mode == COOLING) {
        Serial.println("COOLING");
        if (fan.isNotRunning() || tec.isNotRunning()) {
            fan.start();
            tec.start();
        }
        if (tec.isHeatinng()) {
            tec.cool();
        }
    } else if (faircon.mode == HEATING) {
        Serial.println("HEATING");
        if (fan.isNotRunning() || tec.isNotRunning()) {
            fan.start();
            tec.start();
        }
        if (tec.isCooling()) {
            tec.heat();
        }
    }
}

// Will be executed when user changes the controller configuration.
void handelControllerChange() {
    if (func.hasControllerFanSpeedChanged()) {
        fan.setSpeed(faircon.controller.fanSpeed);
    }
    if (func.hasControllerTempChanged()) {
    }
    if (func.hasControllerVoltageChanged()) {
        tec.setVoltage(faircon.controller.tecVoltage);
    }
    cache.save();
}

void checkState() {
    if (faircon.mode == COOLING || faircon.mode == HEATING) {
        float requiredTemp = faircon.controller.temperature;
        float roomTemperature = roomTemp.value();
        float tecTemperature = tecTemp.value();
        if (tecTemperature > 80) {
            faircon.status = TEC_OVERHEATING;
        } else if (tecTemperature > 70) {
            faircon.status = TEC_HEATING;
        } else {
            if (roomTemperature > requiredTemp + 0.5) {
                faircon.status = TRANSITION_DEC;
            } else if (roomTemperature < requiredTemp - 0.5) {
                faircon.status = TRANSITION_INC;
            } else {
                faircon.status = STABLE;
            }
        }
    } else {
        faircon.status = STABLE;
    }
}

void handleStableState() {
    if (faircon.status = STABLE) {
        fan.setSpeed(faircon.controller.fanSpeed);
        tec.setVoltage(faircon.controller.tecVoltage);
    }
}

// This code handles the OVERHEATING state of FAIRCON.
void handleOverHeating() {
    if (faircon.mode == COOLING) {
        if (faircon.status = TEC_OVERHEATING) {
            tec.stop();
            fan.faster();
        } else if (faircon.status = TEC_HEATING) {
            tec.slower();
            fan.faster();
        }
    }
}

// In cooling and heating mode, bring the roomTemp closer to requiredTemp
// with precision of 0.5C.
// This code will be executed only if FAIRCON is not in OVERHEATING state
void handleTempTransition() {
    if (faircon.status = TRANSITION_DEC) {
        fan.slower();
        tec.faster();
    } else if (faircon.status = TRANSITION_INC) {
        fan.faster();
        tec.slower();
    }
}
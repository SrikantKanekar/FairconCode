#include "src/Cache.h"
#include "src/Fan/Fan.h"
#include "src/Function.h"
#include "src/LM35/LM35.h"
#include "src/RestApiServer.h"
#include "src/Structure.h"
#include "src/Tec/Tec.h"
#include "src/WiFiConnect/WiFiConnectAP.h"

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
    Serial.begin(115200);
    wiFi.start();
    fan.init();
    tec.init();
}

void loop(void) {
    server.handleClient();
    currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
        handleFaircon();
        previousData = faircon;
        previousMillis = currentMillis;
    }
}

void handleFaircon() {
    if (func.hasModeChanged()) {
        handelModeChange();
    }
    if (func.hasControllerChanged()) {
        handelControllerChange();
    }
    handlePID();
    handleOverHeating();
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
        cache.save();
    } else if (faircon.mode == FAN) {
        Serial.println("FAN");
        if (tec.isRunning()) {
            tec.stop();
        }
        if (!fan.isRunning()) {
            fan.start();
        }
    } else if (faircon.mode == COOLING) {
        Serial.println("COOLING");
        if (!fan.isRunning() || !tec.isRunning()) {
            fan.start();
            tec.start();
        }
        if (!tec.isCooling()) {
            tec.cool();
        }
    } else if (faircon.mode == HEATING) {
        Serial.println("HEATING");
        if (!fan.isRunning() || !tec.isRunning()) {
            fan.start();
            tec.start();
        }
        if (tec.isCooling()) {
            tec.heat();
        }
    }
}

void handelControllerChange() {
    if (func.hasControllerFanSpeedChanged()) {
        fan.setSpeed(faircon.controller.fanSpeed);
    }
    if (func.hasControllerTempChanged()) {
    }
    if (func.hasControllerVoltageChanged()) {
        tec.setVoltage(faircon.controller.tecVoltage);
    }
}

void handlePID() {
    if (faircon.mode == COOLING ||
        faircon.mode == HEATING && faircon.status != OVERHEATING) {
        float required = faircon.controller.temperature;
        float current = roomTemp.value();

        if (current > required + 0.5) {
            fan.faster();
            tec.slower();
            faircon.status = TRANSITION;
        } else if (current < required - 0.5) {
            fan.slower();
            tec.faster();
            faircon.status = TRANSITION;
        } else {
            faircon.status = STABLE;
        }
    }
}

void handleOverHeating() {
    if (faircon.mode == COOLING) {
        float temp = tecTemp.value();
        if (temp > 80) {
            tec.stop();
            fan.faster();
            faircon.status = OVERHEATING;
        } else if (temp > 70) {
            tec.slower();
            fan.faster();
            faircon.status = OVERHEATING;
        } else {
            faircon.status = STABLE;
        }
    }
}
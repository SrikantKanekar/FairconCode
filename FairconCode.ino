#include "src/Cache.h"
#include "src/Data.h"
#include "src/Fan/Fan.h"
#include "src/RestApiServer.h"
#include "src/Sensor/Sensor.h"
#include "src/Tec/Tec.h"
#include "src/WiFiConnect/WiFiConnectAP.h"

// Function definations
void handleFaircon();
void handelModeChange();
void checkState();
void handleStableState();
void handleTransitionState();
void handleOverHeatingState();

Faircon faircon;
Faircon previousData;
WiFiConnectAP wiFi;
Cache cache(&faircon);
RestApiServer server(&faircon);
Sensor sensor;
Tec tec;
Fan fan;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
const long interval = 10000;

void setup(void) {
    Serial.begin(115200);
    Serial.println();
    Serial.println("///////////////////////START//////////////////////");
    wiFi.start();
    cache.init();
    server.init();
    sensor.init();
    fan.init();
    tec.init();
    previousData = faircon;
}

// handleFaircon() is executed with some delay to reduce the load on the cpu.
void loop(void) {
    server.handleClient();

    currentMillis = millis();
    if (currentMillis - previousMillis > interval) {
        digitalWrite(D4, HIGH);
        Serial.println("<------------------LOOP---------------->");
        handleFaircon();
        previousData = faircon;
        previousMillis = currentMillis;
        digitalWrite(D4, LOW);
    }
}

// This function is execute after every 10 seconds.
void handleFaircon() {
    handelModeChange();
    cache.save();
    checkState();
    handleStableState();
    handleTransitionState();
    handleOverHeatingState();
}

// Executed everytime user changes the Mode.
void handelModeChange() {
    if (faircon.mode != previousData.mode) {
        Serial.print("Main           --> Faircon Mode Changed : ");
        if (faircon.mode == IDLE) {
            Serial.println("IDLE");
            fan.stop();
            tec.stop();
        } else if (faircon.mode == FAN) {
            Serial.println("FAN");
            tec.stop();
            fan.start();
        } else if (faircon.mode == COOLING) {
            Serial.println("COOLING");
            fan.start();
            tec.start();
            tec.cool();
        } else if (faircon.mode == HEATING) {
            Serial.println("HEATING");
            fan.start();
            tec.start();
            tec.heat();
        }
    }
}

// Will check the statue of the Faircon
// First it will check if the Tec modules are overheating.
// If it doesn't, then it will check for Transition state.
// Else it will be in stable state.
void checkState() {
    Serial.print("Main           --> CheckState ->");
    if (faircon.mode == COOLING || faircon.mode == HEATING) {
        float requiredTemp = faircon.controller.temperature;
        float roomTemperature = sensor.roomValue();
        float tecTemperature = sensor.tecValue();

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
        Serial.print(" requiredTemp: ");
        Serial.print(requiredTemp);

        Serial.print(", roomTemperature: ");
        Serial.print(roomTemperature);

        Serial.print(", tecTemperature: ");
        Serial.print(tecTemperature);
    } else {
        faircon.status = STABLE;
    }
    Serial.print(" Status: ");
    Serial.println(faircon.status);
}

// If Faircon is in stable state, it will set the fan speed and tec as requested by the user.
void handleStableState() {
    if (faircon.status == STABLE) {
        fan.setSpeed(faircon.controller.fanSpeed);
        tec.setVoltage(faircon.controller.tecVoltage);
    }
}

void handleTransitionState() {
    if (faircon.mode == COOLING || faircon.mode == HEATING) {
        if (faircon.status == TRANSITION_DEC) {
            fan.slower();
            tec.faster();
        } else if (faircon.status == TRANSITION_INC) {
            fan.faster();
            tec.slower();
        }
    }
}

// This code handles the OVERHEATING state of FAIRCON.
void handleOverHeatingState() {
    if (faircon.mode == COOLING || faircon.mode == HEATING) {
        if (faircon.status == TEC_OVERHEATING) {
            tec.stop();
            fan.faster();
        } else if (faircon.status == TEC_HEATING) {
            tec.slower();
            fan.faster();
        } else {
            if (!tec.isTecRunning()) {
                tec.start();
            }
        }
    }
}
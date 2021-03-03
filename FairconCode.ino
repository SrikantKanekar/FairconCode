#include "src/RestApi/RestApiServer.h"
#include "src/WiFiConnect/WiFiConnectAP.h"

WiFiConnectAP myWiFi;
RestApiServer restServer(1,1,1);

void setup(void) {
    Serial.begin(115200);
    myWiFi.start();
}

unsigned long previousMillis = 0;
const long interval = 15000;

void loop(void) {
    restServer.handleClient();

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > interval){
        previousMillis = currentMillis;
        restServer.setParameters(2,2,2);
    }
}

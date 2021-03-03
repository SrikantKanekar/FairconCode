#include "src/WiFiConnect/WiFiConnectBoth.h"

WiFiConnectBoth myWiFi("FAIRCON", "12345678", "Z2 plus", "12345678");

void setup(){
    Serial.begin(115200);
    myWiFi.startAP();
    myWiFi.connectSTA();
}

void loop(){

}
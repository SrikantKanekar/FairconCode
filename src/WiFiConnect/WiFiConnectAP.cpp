#include "WiFiConnectAP.h"

#include "Arduino.h"
#include "ESP8266WiFi.h"

const char* _ssid = "FAIRCON";
const char* _password = "12345678";

void WiFiConnectAP::start() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(_ssid, _password);

    Serial.print("WiFiConnectAP  --> WiFi Access Point Started, ");
    Serial.print("IP address : ");
    Serial.println(WiFi.softAPIP());
}
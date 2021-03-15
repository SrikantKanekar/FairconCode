#include "WiFiConnectAP.h"

#include "Arduino.h"
#include "ESP8266WiFi.h"

const char* _ssid = "FAIRCON";
const char* _password = "12345678";

void WiFiConnectAP::start() {
    Serial.println();
    Serial.println("Configuring Access Point......");

    WiFi.mode(WIFI_AP);
    WiFi.softAP(_ssid, _password);

    Serial.print("AP IP address is : ");
    Serial.println(WiFi.softAPIP());
}
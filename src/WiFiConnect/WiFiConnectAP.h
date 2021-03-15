/*
 * WiFiConnectAP - Library for connecting Esp8266 in AP Mode.
 * Empty Constructor (should be called above setup function)
 * ssid -> FAIRCON
 * password -> 12345678
 * start -> start AP in nodemcu (must be called in setUp function)
 */

#ifndef WiFiConnectAP_h
#define WiFiConnectAP_h

#include "Arduino.h"
#include "ESP8266WiFi.h"

class WiFiConnectAP {
   public:
    void start();
};

#endif
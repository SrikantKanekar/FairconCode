/*
 * WiFiConnectSTA - Library for connecting Esp8266 in Station Mode.
 * Constructor accepts ssid and password (should be called above setup function)
 * ssid -> ssid of Router or hotspot
 * password -> Password
 * connect -> start connecting nodemcu to router or hotspot (must be called in setUp function)
 */

#ifndef WiFiConnectSTA_h
#define WiFiConnectSTA_h

#include "Arduino.h"
#include "ESP8266WiFi.h"

class WiFiConnectSTA {
   private:
    char *_ssid;
    char *_password;

   public:
    WiFiConnectSTA(char *ssid, char *password);
    void connect();
    uint8_t status();
};

#endif
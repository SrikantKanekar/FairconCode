/*
 * WiFiConnectBoth - Library for connecting Esp8266 in Station and AP Mode.
 * Constructor accepts ssid and password for STA Mode.
 * startAP -> start Nodemcu Access Point
 * connectSTA -> start connecting nodemcu to router or hotspot
 */

#ifndef WiFiConnectBoth_h
#define WiFiConnectBoth_h

#include "Arduino.h"
#include "ESP8266WiFi.h"

class WiFiConnectBoth
{
private:
    char *_STA_ssid;
    char *_STA_password;
public:
    WiFiConnectBoth(char *sta_ssid, char *sta_password);
    void startAP();
    void connectSTA();
};

#endif
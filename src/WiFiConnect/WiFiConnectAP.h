/*
 * WiFiConnectAP - Library for connecting Esp8266 in AP Mode.
 * Constructor accepts ssid and password (should be called above setup function)
 * ssid -> ssid of Access Point
 * password -> Password
 * start -> start AP in nodemcu (must be called in setUp function)
 */

#ifndef WiFiConnectAP_h
#define WiFiConnectAP_h

#include "Arduino.h"
#include "ESP8266WiFi.h"

class WiFiConnectAP
{
private:
    char *_ssid;
    char *_password;
public:
    WiFiConnectAP(char *ssid, char *password);
    void start();
};

#endif
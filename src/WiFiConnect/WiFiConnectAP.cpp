#include "Arduino.h"
#include "WiFiConnectAP.h"
#include "ESP8266WiFi.h"

WiFiConnectAP::WiFiConnectAP(char *ssid, char *password){
    _ssid = ssid;
    _password = password;
}

void WiFiConnectAP::start(){
    Serial.println();
    Serial.println("Configuring Access Point......");
    
    WiFi.mode(WIFI_AP);
    WiFi.softAP(_ssid, _password);
    
    Serial.print("AP IP address is : ");
    Serial.println(WiFi.softAPIP());
}
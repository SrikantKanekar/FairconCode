#include "Arduino.h"
#include "WiFiConnectBoth.h"
#include "ESP8266WiFi.h"

WiFiConnectBoth::WiFiConnectBoth(char *ap_ssid, char *ap_password, char *sta_ssid, char *sta_password){
    WiFi.mode(WIFI_AP_STA);
    _AP_ssid = ap_ssid;
    _AP_password = ap_password;
    _STA_ssid = sta_ssid;
    _STA_password = sta_password;
}

void WiFiConnectBoth::startAP(){
    Serial.println();
    Serial.println("Configuring Access Point......");
    
    WiFi.softAP(_AP_ssid, _AP_password);
    
    Serial.print("AP IP address is : ");
    Serial.println(WiFi.softAPIP());
}

void WiFiConnectBoth::connectSTA(){
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(_STA_ssid);
    
    WiFi.begin(_STA_ssid, _STA_password);
    
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi Connected");
    Serial.print("IP address is : ");
    Serial.println(WiFi.localIP());
}
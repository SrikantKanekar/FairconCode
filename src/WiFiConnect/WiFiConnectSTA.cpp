#include "Arduino.h"
#include "WiFiConnectSTA.h"
#include "ESP8266WiFi.h"

WiFiConnectSTA::WiFiConnectSTA(char *ssid, char *password){
    _ssid = ssid;
    _password = password;
}

void WiFiConnectSTA::connect(){
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(_ssid);
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _password);
    
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
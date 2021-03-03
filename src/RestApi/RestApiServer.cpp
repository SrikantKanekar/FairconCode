#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "RestApiServer.h"

float _motorSpeed;
float _temperature;
float _voltage;

ESP8266WebServer RestServer(80);

void welcome()
{
    RestServer.send(200, "text/html", "Welcome to FAIRCON REST Web Server");
}

void GET_Parameters()
{
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject &jsonObj = jsonBuffer.createObject();
    char JSONmessageBuffer[200];

    jsonObj["motor"] = _motorSpeed;
    jsonObj["temperature"] = _temperature;
    jsonObj["voltage"] = _voltage;

    jsonObj.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    RestServer.send(200, "application/json", JSONmessageBuffer);
}

void printParameters()
{
    Serial.println("\nParameters Updated");
    Serial.print("Motor : ");
    Serial.println(_motorSpeed);
    Serial.print("Temperature : ");
    Serial.println(_temperature);
    Serial.print("Voltage : ");
    Serial.println(_voltage);
}

void PUT_Parameters()
{
    StaticJsonBuffer<500> jsonBuffer;
    String body = RestServer.arg("plain");
    JsonObject &jsonBody = jsonBuffer.parseObject(body);

    if (jsonBody.success())
    {
        _motorSpeed = jsonBody["motor"];
        _temperature = jsonBody["temperature"];
        _voltage = jsonBody["voltage"];
        printParameters();
        RestServer.send(200);
    }
    else
    {
        Serial.println("error in parsing json body");
        RestServer.send(400);
    }
}

void configure_routing()
{
    RestServer.on("/", HTTP_GET, welcome);
    RestServer.on("/parameter", HTTP_GET, GET_Parameters);
    RestServer.on("/parameter", HTTP_PUT, PUT_Parameters);
}

RestApiServer::RestApiServer(float motorSpeed, float temperature, float voltage)
{
    _motorSpeed = motorSpeed;
    _temperature = temperature;
    _voltage = voltage;

    configure_routing();
    RestServer.begin();
    Serial.println("FAIRCON REST Server Started.");
}

void RestApiServer::setParameters(float motorSpeed, float temperature, float voltage)
{
    _motorSpeed = motorSpeed;
    _temperature = temperature;
    _voltage = voltage;
    printParameters();
}

float RestApiServer::getMotorSpeed()
{
    return _motorSpeed;
}

float RestApiServer::getTemperature()
{
    return _temperature;
}

float RestApiServer::getVoltage()
{
    return _voltage;
}

void RestApiServer::handleClient()
{
    RestServer.handleClient();
}
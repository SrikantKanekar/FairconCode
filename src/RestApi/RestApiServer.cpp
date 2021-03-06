#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include "RestApiServer.h"

ESP8266WebServer RestServer(80);
Data data;

void welcome()
{
    RestServer.send(200, "text/html", "Welcome to FAIRCON");
}

void GET_Parameters()
{
    StaticJsonDocument<48> doc;
    String output;

    doc["fanSpeed"] = data.home.fanSpeed;
    doc["temperature"] = data.home.temperature;
    doc["tecVoltage"] = data.home.tecVoltage;

    serializeJson(doc, output);
    RestServer.send(200, "application/json", output);
}

void GET_Controller()
{
    StaticJsonDocument<48> doc;
    String output;

    doc["fanSpeed"] = data.controller.fanSpeed;
    doc["temperature"] = data.controller.temperature;
    doc["tecVoltage"] = data.controller.tecVoltage;

    serializeJson(doc, output);
    RestServer.send(200, "application/json", output);
}

void PUT_FanSpeed()
{
    StaticJsonDocument<48> inputDoc;
    StaticJsonDocument<48> outputDoc;
    String input = RestServer.arg("plain");
    String output;

    DeserializationError error = deserializeJson(inputDoc, input);

    if (!error)
    {
        data.controller.fanSpeed = inputDoc["fanSpeed"];
        Serial.println("");
        Serial.print("FanSpeed Updated : ");
        Serial.print(data.controller.fanSpeed);
        Serial.println(" RPM");
        outputDoc["response"] = "SUCCESS";
    }
    else
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        outputDoc["response"] = "Deserialization error";
    }
    serializeJson(outputDoc, output);
    RestServer.send(200, "application/json", output);
}

void PUT_Temperature()
{
    StaticJsonDocument<48> inputDoc;
    StaticJsonDocument<48> outputDoc;
    String input = RestServer.arg("plain");
    String output;

    DeserializationError error = deserializeJson(inputDoc, input);

    if (!error)
    {
        data.controller.temperature = inputDoc["temperature"];
        Serial.println("");
        Serial.print("Temperature Updated : ");
        Serial.print(data.controller.temperature);
        Serial.println(" C");
        outputDoc["response"] = "SUCCESS";
    }
    else
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        outputDoc["response"] = "Deserialization error";
    }
    serializeJson(outputDoc, output);
    RestServer.send(200, "application/json", output);
}

void PUT_TecVoltage()
{
    StaticJsonDocument<48> inputDoc;
    StaticJsonDocument<48> outputDoc;
    String input = RestServer.arg("plain");
    String output;

    DeserializationError error = deserializeJson(inputDoc, input);

    if (!error)
    {
        data.controller.tecVoltage = inputDoc["tecVoltage"];
        Serial.println("");
        Serial.print("Tec Voltage Updated : ");
        Serial.print(data.controller.tecVoltage);
        Serial.println(" V");
        outputDoc["response"] = "SUCCESS";
    }
    else
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        outputDoc["response"] = "Deserialization error";
    }
    serializeJson(outputDoc, output);
    RestServer.send(200, "application/json", output);
}

void configure_routing()
{
    RestServer.on("/", HTTP_GET, welcome);
    RestServer.on("/home/parameters", HTTP_GET, GET_Parameters);
    RestServer.on("/controller/sync", HTTP_GET, GET_Controller);
    RestServer.on("/controller/fanSpeed", HTTP_PUT, PUT_FanSpeed);
    RestServer.on("/controller/temperature", HTTP_PUT, PUT_Temperature);
    RestServer.on("/controller/tecVoltage", HTTP_PUT, PUT_TecVoltage);
}

void RestApiServer::init()
{
    configure_routing();
    RestServer.begin();
    Serial.println("FAIRCON REST Server Started.");
    
    EEPROM.begin(30);
    EEPROM.get(0, data);
    Serial.println("FAIRCON data initialised");
}

void RestApiServer::handleClient()
{
    RestServer.handleClient();
}

void RestApiServer::commit(){
    EEPROM.put(0, data);
    EEPROM.commit();  
    Serial.println("Cache data Commited");
}

// Home Setters
void RestApiServer::set_HOME_Parameters(uint16_t fanSpeed, float temperature, float tecVoltage)
{
    data.home.fanSpeed = fanSpeed;
    data.home.temperature = temperature;
    data.home.tecVoltage = tecVoltage;
    Serial.println("Home Parameters updated in Faircon");
}

//Controller Getters
uint16_t RestApiServer::get_CONTROLLER_FanSpeed()
{
    return data.controller.fanSpeed;
}

float RestApiServer::get_CONTROLLER_Temperature()
{
    return data.controller.temperature;
}

float RestApiServer::get_CONTROLLER_TecVoltage()
{
    return data.controller.tecVoltage;
}

Data RestApiServer::getData(){
    return data;
}

void RestApiServer::printData(Data currentData)
{
    Serial.println("");
    Serial.println("Home");
    Serial.print("Fan Speed : ");
    Serial.println(currentData.home.fanSpeed);
    Serial.print("Temperature : ");
    Serial.println(currentData.home.temperature);
    Serial.print("Tec Voltage : ");
    Serial.println(currentData.home.tecVoltage);

    Serial.println("");
    Serial.println("Controller");
    Serial.print("Fan Speed : ");
    Serial.println(currentData.controller.fanSpeed);
    Serial.print("Temperature : ");
    Serial.println(currentData.controller.temperature);
    Serial.print("Tec Voltage : ");
    Serial.println(currentData.controller.tecVoltage);

    Serial.println("");
    Serial.print("Mode : ");
    Serial.println(currentData.mode);

    Serial.println("");
    Serial.print("Total Data Size : ");
    Serial.println(sizeof(data));
}

bool isDataEqual(Data current, Data stored)
{
    return current.home.fanSpeed == stored.home.fanSpeed &&
           current.home.temperature == stored.home.temperature &&
           current.home.tecVoltage == stored.home.tecVoltage &&
           current.controller.fanSpeed == stored.controller.fanSpeed &&
           current.controller.temperature == stored.controller.temperature &&
           current.controller.tecVoltage == stored.controller.tecVoltage &&
           current.mode == stored.mode;
}

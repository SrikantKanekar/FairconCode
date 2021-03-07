#include "RestApiServer.h"

void handelModeChange();

ESP8266WebServer RestServer(80);
Cache cache;
Structure data;

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
    doc["mode"] = data.mode;

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

void PUT_Mode()
{
    StaticJsonDocument<48> inputDoc;
    StaticJsonDocument<48> outputDoc;
    String input = RestServer.arg("plain");
    String output;

    DeserializationError error = deserializeJson(inputDoc, input);

    if (!error)
    {
        data.mode = inputDoc["mode"];
        Serial.println("");
        Serial.print("Mode Updated : ");
        Serial.println(data.mode);
        outputDoc["response"] = "SUCCESS";
        handelModeChange();
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
    RestServer.on("/home/mode", HTTP_PUT, PUT_Mode);
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
    data = cache.init();
}

void RestApiServer::handleClient()
{
    RestServer.handleClient();
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

Structure RestApiServer::getData(){
    return data;
}

void handelModeChange(){
    if (data.mode == 0)
    {
        Serial.println("FAIRCON ON mode started");
        cache.commit(data);        
    } else if (data.mode == 2)
    {
        Serial.println("Started cooling");
    }    
}
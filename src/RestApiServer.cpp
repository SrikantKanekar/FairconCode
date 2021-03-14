#include "RestApiServer.h"

void handelModeChange();

ESP8266WebServer RestServer(80);
Faircon *faircon;

void welcome()
{
    RestServer.send(200, "text/html", "Welcome to FAIRCON");
}

void TEST_FAIRCON()
{
    StaticJsonDocument<48> doc;
    String output;

    doc["response"] = "SUCCESS";
    
    serializeJson(doc, output);
    RestServer.send(200, "application/json", output);
}

void GET_Parameters()
{
    StaticJsonDocument<48> doc;
    String output;

    doc["fanSpeed"] = (*faircon).home.fanSpeed;
    doc["temperature"] = (*faircon).home.temperature;
    doc["tecVoltage"] = (*faircon).home.tecVoltage;

    serializeJson(doc, output);
    RestServer.send(200, "application/json", output);
}

void GET_Controller()
{
    StaticJsonDocument<48> doc;
    String output;

    doc["fanSpeed"] = (*faircon).controller.fanSpeed;
    doc["temperature"] = (*faircon).controller.temperature;
    doc["tecVoltage"] = (*faircon).controller.tecVoltage;
    doc["mode"] = (*faircon).mode;

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
        (*faircon).controller.fanSpeed = inputDoc["fanSpeed"];
        Serial.println("");
        Serial.print("FanSpeed Updated : ");
        Serial.print((*faircon).controller.fanSpeed);
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
        (*faircon).controller.temperature = inputDoc["temperature"];
        Serial.println("");
        Serial.print("Temperature Updated : ");
        Serial.print((*faircon).controller.temperature);
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
        (*faircon).controller.tecVoltage = inputDoc["tecVoltage"];
        Serial.println("");
        Serial.print("Tec Voltage Updated : ");
        Serial.print((*faircon).controller.tecVoltage);
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
        (*faircon).mode = inputDoc["mode"];
        Serial.println("");
        Serial.print("Mode Updated : ");
        Serial.println((*faircon).mode);
        outputDoc["response"] = "SUCCESS";
        // handelModeChange();
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
    RestServer.on("/home/test", HTTP_GET, TEST_FAIRCON);
    RestServer.on("/controller/sync", HTTP_GET, GET_Controller);
    RestServer.on("/controller/fanSpeed", HTTP_PUT, PUT_FanSpeed);
    RestServer.on("/controller/temperature", HTTP_PUT, PUT_Temperature);
    RestServer.on("/controller/tecVoltage", HTTP_PUT, PUT_TecVoltage);
}

RestApiServer::RestApiServer(Faircon* Faircon){
    faircon = Faircon;
    configure_routing();
    RestServer.begin();
    Serial.println("FAIRCON REST Server Started.");
}

void RestApiServer::handleClient()
{
    RestServer.handleClient();
}
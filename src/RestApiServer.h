/*
 * RestApiServer - Library which provides rest endpoints for parameter values.
 * Call Constructor above setup function and pass motor speed, temp, voltage respectively.
 * call handleClient in loop function.
 */

#ifndef RestApiServer_h
#define RestApiServer_h

#include "ArduinoJson.h"
#include "ESP8266WebServer.h"

#include "Data.h"

class RestApiServer {
   public:
    RestApiServer(Faircon *Faircon);
    void init();
    void handleClient();
};

#endif
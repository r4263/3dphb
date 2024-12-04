#ifndef REQUEST_MIDDLEWARE_H
#define REQUEST_MIDDLEWARE_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <src/data/hash.h>

bool validateRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len);

#endif
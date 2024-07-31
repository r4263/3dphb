#ifndef WMANAGER_H
#define WMANAGER_H

#include <Arduino.h>
#include <src/data.h>
#include <src/definitions.h>
#include <src/constants.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncUDP.h>
#include <src/wTools.h>

extern void wManager(void *pvParameters);
extern TaskHandle_t wManagerHandle;

#endif
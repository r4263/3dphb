#ifndef WMANAGER_H
#define WMANAGER_H

#include <Arduino.h>
#include <src/data.h>
#include <src/definitions.h>
#include <WiFi.h>

extern void wManager(void *pvParameters);
extern TaskHandle_t wManagerHandle;

#endif
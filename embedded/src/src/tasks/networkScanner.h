#ifndef NETWORKSCANNER_H
#define NETWORKSCANNER_H

#include <src/definitions.h>
#include <Arduino.h>
#include <WiFi.h>

extern void networkScanner(void *pvParameters);
extern TaskHandle_t nScannerHandle;

#endif
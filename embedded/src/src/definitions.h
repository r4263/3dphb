#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SHA256.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#include <src/filetools.h>
#include <src/constants.h>
#include <src/tasks/init.h>
#include <src/tasks/wManager.h>
#include <src/tasks/networkScanner.h>

#include <src/data.h>

// --- Interfaces ---
extern Connection networkConfig;
extern status FS_STAT;
extern status W_STAT;
Connection networkConfig;

// --- Mutexes handles ---
SemaphoreHandle_t wMutex;     // wireless connection manager mutex handle
SemaphoreHandle_t stateMutex; // status manager mutex handle

// --- Tasks and function prototypes ---

// --- Task Handles ---

// --- Objects ---
JsonDocument config;
SHA256 crypto;

//  --- RTOS Variables ---
TickType_t xLastWakeTime;

// --- Variables ---
int i = 0;
byte sha256_output[32];

#endif
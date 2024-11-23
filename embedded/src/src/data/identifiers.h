/**
 * A place resigned to global access control identifiers, mutexes and types
 */

#ifndef IDENTIFIERS_H
#define IDENTIFIERS_H

#include <Arduino.h>
#include <src/data/types.h>

extern SemaphoreHandle_t fileSystemMutex;
extern SemaphoreHandle_t globalStateMutex;
extern SemaphoreHandle_t fileSystemMutex;
extern SemaphoreHandle_t networkOperationsMutex;
extern SemaphoreHandle_t networkStateMutex;

extern BeeperActions beeperNotificationValue;

// Task Handles
extern TaskHandle_t beeperHandle;
extern TaskHandle_t networkScannerHandle;
extern TaskHandle_t networkManagerHandle;
extern TaskHandle_t pProcessingHandle;
extern TaskHandle_t hmiHandle;

#endif
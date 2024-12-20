#include <src/data/identifiers.h>

BeeperActions beeperNotificationValue;

TaskHandle_t beeperHandle;
TaskHandle_t networkScannerHandle;
TaskHandle_t pProcessingHandle;
TaskHandle_t networkManagerHandle;
TaskHandle_t hmiHandle;

SemaphoreHandle_t fileSystemMutex;
SemaphoreHandle_t globalStateMutex;
SemaphoreHandle_t networkOperationsMutex;
SemaphoreHandle_t networkStateMutex;
#include <src/data/data.h>

GlobalState APPLICATION_STATE;
NetworkState NETWORK_STATE;

boolean initializeMutexes(void)
{
    globalStateMutex = xSemaphoreCreateMutex();
    fileSystemMutex = xSemaphoreCreateMutex();
    networkStateMutex = xSemaphoreCreateMutex();

    return globalStateMutex != NULL &&
           fileSystemMutex != NULL &&
           networkStateMutex != NULL;
}
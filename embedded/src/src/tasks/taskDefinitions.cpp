#include <src/tasks/taskDefinitions.h>

void initializeTasks(void)
{
    // xTaskCreatePinnedToCore(Function, Task name, Stack size, Parameter, Priority, Handle, Code ID);
    xTaskCreatePinnedToCore(networkManager, "WirelessManagerTask", 16384, NULL, 1, &networkManagerHandle, 0);
    xTaskCreatePinnedToCore(peripheralProcessing, "PeripheralProcessingTask", 8192, NULL, 5, &pProcessingHandle, 1);
    xTaskCreatePinnedToCore(beeper, "BeeperTask", 4096, NULL, 9, &beeperHandle, 1);
    xTaskCreatePinnedToCore(hmiHandler, "HMITask", 8192, NULL, 9, &hmiHandle, 1);
}
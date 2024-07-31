#include <src/tasks/networkScanner.h>

TaskHandle_t nScannerHandle;

void networkScanner(void *pvParameters)
{
    xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(30000));
        Serial.println("tick");

        // Perform action here.
    }
}
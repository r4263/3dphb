#include <Arduino.h>

TaskHandle_t InitTask;

void Init(void *pvParameters)
{
    Serial.print("FUNCIONAAA!");
    vTaskDelete(InitTask);
}
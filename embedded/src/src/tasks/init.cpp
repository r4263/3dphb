#include <src/tasks/init.h>

void Init(void *pvParameters)
{
    while (true)
    {
        float temp_celsius = temperatureRead();

        Serial.print("Temp onBoard ");
        Serial.print(temp_celsius);
        Serial.println("C");

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    // vTaskDelete(InitTask);
}
#include <src/tasks/beeper.h>

void beeper(void *pvParameters)
{
    while (true)
    {
        xTaskNotifyWait(0x00, 0xFFFFFFFF, (uint32_t *)&beeperNotificationValue, portMAX_DELAY);

        if (beeperNotificationValue)
        {
            ledcSetup(2, 440, 10);
            ledcWrite(2, 512);
            vTaskDelay(pdMS_TO_TICKS(500));
            ledcWrite(2, 0);
        }
        else
        {
            ledcSetup(2, 1200, 10);
            ledcWrite(2, 512);
            vTaskDelay(pdMS_TO_TICKS(500));
            ledcWrite(2, 0);
        }
        // xTaskNotify(beeperHandle, BEEP, eSetValueWithOverwrite); // -> usage as beep
        // xTaskNotify(beeperHandle, TEST, eSetValueWithOverwrite); // -> usage as a test
    }
}
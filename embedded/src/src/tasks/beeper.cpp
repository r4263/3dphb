#include <src/tasks/beeper.h>

uint16_t currentFreq;
uint16_t desiredFreq;

void beeper(void *pvParameters)
{
    while (true)
    {
        xTaskNotifyWait(0x00, 0xFFFFFFFF, (uint32_t *)&beeperNotificationValue, portMAX_DELAY);

        currentFreq = ledcReadFreq(BUZZER_CHANNEL);
        desiredFreq = APPLICATION_STATE.getTone();

        if (beeperNotificationValue)
        {
            if (currentFreq != desiredFreq)
                ledcSetup(BUZZER_CHANNEL, desiredFreq, 10);
            ledcWrite(BUZZER_CHANNEL, turn_on);
            vTaskDelay(pdMS_TO_TICKS(APPLICATION_STATE.getDuration()));
            ledcWrite(BUZZER_CHANNEL, turn_off);
        }
        // else
        // {
        //     ledcSetup(BUZZER_CHANNEL, 1200, 10);
        //     ledcWrite(2, 512);
        //     vTaskDelay(pdMS_TO_TICKS(500));
        //     ledcWrite(2, 0);
        // }
        // xTaskNotify(beeperHandle, BEEP, eSetValueWithOverwrite); // -> usage as beep
        // xTaskNotify(beeperHandle, TEST, eSetValueWithOverwrite); // -> usage as a test
    }
}
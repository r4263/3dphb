#include <src/tasks/wManager.h>
#include <src/wTools.h>

TaskHandle_t wManagerHandle;
status W_STAT;

// https://macvendors.com/query/{MACADDR}

void wManager(void *pvParameters)
{
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.enableLongRange(true);

    while (true)
    {
        String nw;
        serializeJson(getNearbyNetworks(), nw);
        Serial.println(nw);
        Serial.println(uxTaskGetStackHighWaterMark2(wManagerHandle));
        vTaskDelay(pdMS_TO_TICKS(2500));
    }
}
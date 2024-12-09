#include <src/tasks/networkScanner.h>

void networkScanner(void *pvParameters)
{
    // TickType_t xLastWakeTime = xTaskGetTickCount();

    uint8_t networkCount = WiFi.scanNetworks();

    String scanContent;

    // for (;;)
    // {
    //     vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(30000));

    JsonDocument doc;

    JsonArray array = doc.to<JsonArray>();

    JsonObject network = array.createNestedObject();
    network["ssid"] = "teste";
    network["encType"] = "Open";
    network["rssi"] = -72;
    network["channel"] = 6;

    serializeJson(doc, scanContent);
    // }
}
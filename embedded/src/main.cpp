#include <Arduino.h>
#include <ArduinoJson.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#include <src/data.h>
#include <src/definitions.h>
#include <src/constants.h>

#include <src/filetools.h>

#include <src/tasks/init.h>
#include <src/tasks/wManager.h>

//--- Interfaces ---
Connection networkConfig;

// --- Objects ---
JsonDocument config;

void setup()
{
    Serial.begin(115200);
    initFS();

    Serial.println(FS_STAT.STATUS ? FS_INIT_OK : FS_STAT.ERR);
    if (!FS_STAT.STATUS)
        return;

    DeserializationError error = deserializeJson(config, readFile(CONFIGPATH));

    networkConfig.setArgs(config["NETWORK"]);

    xTaskCreatePinnedToCore(
        wManager,          /* Function */
        "WirelessManager", /* Task name */
        3072,              /* Stack size */
        NULL,              /* Parameter */
        1,                 /* Priority */
        &wManagerHandle,   /* Handle */
        0                  /* Code ID */
    );

    // xTaskCreate(
    //     Init,                 /* Function */
    //     "InitializationTask", /* Task name */
    //     3072,                 /* Stack size */
    //     NULL,                 /* Parameter */
    //     1,                    /* Priority */
    //     &InitTask             /* Handle */
    // );
}

void loop()
{
}
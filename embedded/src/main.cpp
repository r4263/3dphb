#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <src/filetools.h>
#include <src/tasks/init.h>

// --- Functions & tasks prototypes ---

// ---

// --- Objects ---
Connection networkConfig;

void setup()
{

    // Serial.begin(115200);
    // Serial.print("Init: ");
    // initFS();

    xTaskCreate(
        Init,                 /* Function */
        "InitializationTask", /* Task name */
        3072,                 /* Stack size */
        NULL,                 /* Parameter */
        1,                    /* Priority */
        &InitTask             /* Handle */
    );
}

void loop()
{
}
#include <src/definitions.h>

void setup()
{

    wMutex = xSemaphoreCreateMutex();
    stateMutex = xSemaphoreCreateMutex();

    Serial.begin(115200);
    initFS();

    if (wMutex == NULL)
    {
    }
    else
    {
        Serial.println("Failed to create mutex");
    }

    Serial.println(FS_STAT.STATUS ? FS_INIT_OK : FS_STAT.ERR);
    if (!FS_STAT.STATUS)
        return;

    deserializeJson(config, readFile(CONFIGPATH));

    networkConfig.setArgs(config["NETWORK"]);

    xTaskCreatePinnedToCore(
        wManager,          /* Function */
        "WirelessManager", /* Task name */
        8192,              /* Stack size */
        NULL,              /* Parameter */
        1,                 /* Priority */
        &wManagerHandle,   /* Handle */
        0                  /* Code ID */
    );

    // xTaskCreatePinnedToCore(
    //     networkScanner,   /* Function */
    //     "NetworkScanner", /* Task name */
    //     2048,             /* Stack size */
    //     NULL,             /* Parameter */
    //     0,                /* Priority */
    //     &nScannerHandle,  /* Handle */
    //     0                 /* Code ID */
    // );

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
    String command;
    if (Serial.available())
    {
        command = Serial.readString();
    }

    if (command == "reboot")
    {
        command = "";
        ESP.restart();
    }
    vTaskDelay(pdMS_TO_TICKS(250));

    Serial.print("Contagem: ");
    Serial.println(i);

    i++;
}
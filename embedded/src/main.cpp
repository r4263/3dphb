#include <src/definitions.h>

void setup()
{
  Serial.begin(115200);

  initApplicationVitals(); // Filesystem, variables, mutexes, semaphores...

  // deserializeJson(config, readFile(CONFIGPATH));

  // networkConfig.setArgs(config["NETWORK"]);
}

void loop()
{
  if (Serial.available())
  {
    if (Serial.readString() == "reset")
    {
      ESP.restart();
    }
  }

  vTaskDelay(pdMS_TO_TICKS(200));
}
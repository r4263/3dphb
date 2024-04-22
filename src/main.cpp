#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <assets/data.h>
#include <assets/init.h>

// Defines
#define PIN_NEOPIXEL 48
#define NUMPIXELS 1

// Constants and variables section
const char *ssid = "MAURO";
const char *password = "1003051275";
const TickType_t xDelay250ms = pdMS_TO_TICKS(250);
int connectionTries = 0;

ConnectionConfig config = {1, 'Olá'};

// Libraries and object declarations
Adafruit_NeoPixel statusIndicator(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Task handles
TaskHandle_t Task1;
TaskHandle_t wirelessConnectionManager;

// void TaskCore0(void *pvParameters); //
void connectionMgrTask(void *pvParameters);

void setup()
{
  statusIndicator.begin();
  statusIndicator.setBrightness(5);
  statusIndicator.fill(0x0000FF);
  statusIndicator.show();

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.println(config.connectionType);
  Serial.println(config.SSID);

  while (connectionTries < 20)
  {
    statusIndicator.fill(0xFFFF00);
    statusIndicator.show();
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.print(". ");
    }
    else
    {
      Serial.println("");
      Serial.print("Connected to: ");
      Serial.println(ssid);
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());

      statusIndicator.fill(0x00FF00);
      statusIndicator.show();

      break;
    }
    vTaskDelay(xDelay250ms);
  }
  if (connectionTries >= 19)
  {
    Serial.println("");
    Serial.print("Unable to connect to ");
    Serial.println(ssid);

    statusIndicator.fill(0xFF0000);
    statusIndicator.show();
  }

  // xTaskCreatePinnedToCore(
  //     TaskCore0, /* Function */
  //     "Task1",   /* Task name */
  //     10000,     /* Stack size */
  //     NULL,      /* Parameter */
  //     1,         /* Priority */
  //     &Task1,    /* Handle */
  //     0          /* Pinned core */
  // );
}

// void connectionMgrTask(void *pvParameters)
// {
// }

void loop() {}

// void TaskCore0(void *pvParameters)
// {
//   Serial.print("Task1 running on core ");
//   Serial.println(xPortGetCoreID());

//   while (true)
//   {
//     Serial.println(xPortGetCoreID());
//     Serial.print(" toggle");
//     vTaskDelay(xDelay * 2);
//   }
// }
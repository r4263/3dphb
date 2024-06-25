#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <AsyncUDP.h>
#include <LITTLEFS.h>
#include <ArduinoJson.h>
#include <./assets/data.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <max6675.h>

// Tasks and functions prototypes
void Main(void *pvParameters);
void Init(void *pvParameters);
void TempHandler(void *pvParameters);
void MulticastListener(void *pvParameters);
String readFile(const char *path);
void writeFile(const char *path, const char *content);
double readThermocouple();

// Objects
AsyncUDP udp;
Adafruit_NeoPixel statusIndicator(SLEDN, SLEDPIN, NEO_GRB + NEO_KHZ800);
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
MAX6675 temperatureProbe(MAX6675_SCK, MAX6675_CS, MAX6675_SO);
JsonDocument config;

// Constants and variables section
const TickType_t xDelay250ms = pdMS_TO_TICKS(250);
int connectionTries = 0;

Connection connConfig;

// Task handles
TaskHandle_t WirelessConnectionManager;
TaskHandle_t MulticastListenerHandle;
TaskHandle_t InitTask;
TaskHandle_t MainTask;
TaskHandle_t THandle;

void setup()
{
    xTaskCreate(
        Init,                 /* Function */
        "InitializationTask", /* Task name */
        3072,                 /* Stack size */
        NULL,                 /* Parameter */
        1,                    /* Priority */
        &InitTask             /* Handle */
    );

    while (eTaskGetState(InitTask) != eDeleted)
    {
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    // xTaskCreate(
    //     Main,       /* Function */
    //     "MainTask", /* Task name */
    //     8192,       /* Stack size */
    //     NULL,       /* Parameter */
    //     1,          /* Priority */
    //     &MainTask   /* Handle */
    // );

    xTaskCreate(
        TempHandler,          /* Function */
        "TemperatureHandler", /* Task name */
        4096,                 /* Stack size */
        NULL,                 /* Parameter */
        1,                    /* Priority */
        &THandle              /* Handle */
    );

    xTaskCreatePinnedToCore(
        MulticastListener,        /* Function */
        "MulticastListener",      /* Task name */
        20000,                    /* Stack size */
        NULL,                     /* Parameter */
        1,                        /* Priority */
        &MulticastListenerHandle, /* Handle */
        0                         /* Pinned core */
    );

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

// void loop()
{
}

void Init(void *pvParameters)
{

    // Pre initialization
    LittleFS.end();
    WiFi.disconnect(true);
    tft.init(240, 320);
    tft.setSPISpeed(40000000);
    tft.setTextSize(1);
    tft.fillScreen(0xFFFF);
    tft.setTextColor(0x0000);

    MAX6675 temperatureProbe(12, 8, 13);

    Serial.begin(115200);

    if (!LittleFS.begin())
    {
        Serial.println("An error occurred while mounting LittleFS");
        vTaskDelete(InitTask);
    }

    // // Save data
    // writeFile("/test.txt", "Hello, world!");

    // Read Flash Data
    String content = readFile("/config.cfg");
    deserializeJson(config, content);
    connConfig = {config["nw.ssid"], config["nw.pwk"]};

    tft.println("Stored netowrk settings:");
    tft.print("SSID: ");
    tft.println(connConfig.SSID);
    tft.print("Password: ");
    tft.println(connConfig.PASS);
    tft.println("");

    // Initialize WiFi connection

    WiFi.mode(WIFI_STA);
    WiFi.begin(connConfig.SSID, connConfig.PASS);

    Serial.print("Connecting");
    tft.print("Connecting");

    int count = 0;
    do
    {
        tft.print(".");
        Serial.print(".");
        vTaskDelay(xDelay250ms);
        count++;
    } while ((WiFi.status() != WL_CONNECTED) && (count < 25));

    Serial.println(WiFi.status() == WL_CONNECTED ? " Connected!" : " The connection could not be estabilished! :(");
    Serial.print("Address: ");
    Serial.println(WiFi.localIP());

    tft.println(WiFi.status() == WL_CONNECTED ? " Connected!" : " The connection could not be estabilished! :(");
    tft.print("Address: ");
    tft.println(WiFi.localIP());

    vTaskDelete(InitTask);
}

void Main(void *pvParameters)
{
    while (true)
    {
    }
}

void TempHandler(void *pvParameters)
{
    while (true)
    {
        tft.print("Temp: ");
        // tft.println(temperatureProbe.readCelsius());
        Serial.print("Temp: ");
        // Serial.println(temperatureProbe.readCelsius());
        Serial.println(readThermocouple());
        vTaskDelay(xDelay250ms * 3);
    }
}

void MulticastListener(void *pvParameters)
{
    tft.println("");
    IPAddress multicastIP(227, 77, 77, 7);
    uint16_t multicastPort = 12345;

    if (udp.listenMulticast(multicastIP, multicastPort))
    {
        Serial.print("UDP Multicast Listener started at: ");
        Serial.println(multicastIP);

        tft.println("UDP Multicast Listener started at: ");
        tft.print(multicastIP);
        tft.print(":");
        tft.println(multicastPort);
        udp.onPacket([](AsyncUDPPacket packet)
                     {
                         if (tft.getCursorY() >= 280)
                         {
                             tft.fillScreen(0xFFFF);
                             tft.setCursor(0, 0);
                         }
                         Serial.print("UDP packet received from ");
                         Serial.print(packet.remoteIP());
                         Serial.print(":");
                         Serial.print(packet.remotePort());
                         Serial.print(", type: ");
                         Serial.print(packet.isBroadcast() ? "Broadcast" : (packet.isMulticast() ? "Multicast" : "Normal Packet"));
                         Serial.print(", size: ");
                         Serial.print(packet.length());
                         Serial.print(", data: ");
                         Serial.println((char *)packet.data());

                         tft.println("\n\n");
                         tft.print("Address: ");
                         tft.print(packet.remoteIP());
                         tft.print(":");
                         tft.println(packet.remotePort());
                         tft.print("Type: ");
                         tft.println(packet.isBroadcast() ? "Broadcast" : (packet.isMulticast() ? "Multicast" : "Normal Packet"));
                         tft.print("Size: ");
                         tft.println(packet.length());
                         tft.print("Data: ");
                         tft.println((char *)packet.data());
                         //   udp.print("Received!");
                     });
    }
    else
    {
        Serial.println("Failed to initialize UDP listener.");
        tft.println("Failed to initialize UDP listener.");
    }

    // Loop infinito - necessário para a task.
    while (true)
    {
        vTaskDelay(xDelay250ms * 4);
    }
}

void StatusHandlerTask(void *pvParameters)
{
    // statusIndicator.begin();
    // statusIndicator.setBrightness(5);
    // statusIndicator.fill(0x0000FF);
    // statusIndicator.show();

    // statusIndicator.fill(0x00FF00);
    // statusIndicator.show();

    // statusIndicator.fill(0xFF0000);
    // statusIndicator.show();
}

void writeFile(const char *path, const char *content)
{
    File file = LittleFS.open(path, FILE_WRITE);
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return;
    }

    if (file.print(content))
    {
        Serial.println("File written successfully");
    }
    else
    {
        Serial.println("Write failed");
    }

    file.close();
}

String readFile(const char *path)
{
    File file = LittleFS.open(path);
    if (!file || file.isDirectory())
    {
        Serial.println("Failed to open file for reading");
        return String();
    }

    String content;
    while (file.available())
    {
        content += file.readStringUntil('\n');
    }

    file.close();
    return content;
}

double readThermocouple()
{
    uint16_t v;
    pinMode(MAX6675_CS, OUTPUT);

    digitalWrite(MAX6675_CS, LOW);
    delay(1);

    v = shiftIn(MAX6675_SO, MAX6675_SCK, MSBFIRST);
    v <<= 8;
    v |= shiftIn(MAX6675_SO, MAX6675_SCK, MSBFIRST);

    digitalWrite(MAX6675_CS, HIGH);
    if (v & 0x4)
    {
        return NAN;
    }

    v >>= 3;

    return v * 0.25;
}
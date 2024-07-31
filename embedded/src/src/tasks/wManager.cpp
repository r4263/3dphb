#include <src/tasks/wManager.h>

TaskHandle_t wManagerHandle;
status W_STAT;
AsyncWebServer server(80);
AsyncUDP udp;

// https://macvendors.com/query/{MACADDR}

void wManager(void *pvParameters)
{

    // WiFi.disconnect();
    // WiFi.mode(WIFI_AP);
    // WiFi.enableLongRange(true);
    // WiFi.softAP(networkConfig.INTERNALSSID, networkConfig.INTERNALPASS);
    // Serial.print("SoftAP Address: ");
    // Serial.println(WiFi.softAPIP());

    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.enableLongRange(true);

    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.begin(networkConfig.SSID, networkConfig.PASS);

        Serial.print("Connecting");

        int count = 0;
        do
        {
            Serial.print(".");
            vTaskDelay(pdMS_TO_TICKS(250));
            count++;
        } while ((WiFi.status() != WL_CONNECTED) && (count < 25));

        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.print("Connected! Address: ");
            Serial.println(WiFi.localIP());

            if (WiFi.status() == WL_CONNECTED)
            {
                server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                          {
                            Serial.println(request->args());
                            //AsyncWebServerResponse *response = request->beginResponse(HTTP_STATUS_SERVICE_UNAVAILABLE);
                            AsyncWebServerResponse *response = request->beginResponse(HTTP_STATUS_OK, "application/json", "{'response': 'ok'}");
                            // AsyncWebServerResponse *response = request->beginResponse(HTTP_STATUS_SERVICE_UNAVAILABLE, "application/json", "{'response':'ok'}");
                            response->addHeader("Server", "ESP Async Web Server");
                            request->send(response); });

                if (udp.listenMulticast(networkConfig.MCASTGROUP, networkConfig.MCASTPORT))
                {
                    Serial.print("UDP Multicast Listener started at: ");
                    Serial.println(networkConfig.MCASTGROUP);
                    udp.onPacket([](AsyncUDPPacket packet)
                                 {
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
                                     //   udp.print("Received!");
                                 });
                }
                else
                {
                    Serial.println("Failed to initialize UDP listener.");
                }

                server.begin();
            }
        }
        else
        {
            Serial.println("Could not connect to the specified network!");
        }
    }

    while (true)
    {

        // String nw;
        // serializeJson(getNearbyNetworks(), nw);
        // Serial.println(nw);
        // Serial.println(uxTaskGetStackHighWaterMark(wManagerHandle));

        vTaskDelay(pdMS_TO_TICKS(1));
    }
}
#include <src/tasks/networkManager.h>

// DNS server
DNSServer dnsServer;

// Webservers
AsyncWebServer captivePortal(80);
AsyncWebServer controlPanel(80);
AsyncWebServer api(9000);

// Local state storing
WiFiMode LastWiFiMode = IDLE;
WiFiState LastWiFiState = OFF;

void networkManager(void *pvParameters)
{
  disconnect(AP_MODE);
  disconnect(STA_MODE);

  setUpDNSServer(dnsServer);
  setUpCaptivePortalServer(captivePortal);
  setUpAPIServer(api);

  // NETWORK_STATE.setWiFiMode(STA_MODE);
  // NETWORK_STATE.setWiFiMode(AP_MODE);

  /* Default headers */
  DefaultHeaders::Instance()
      .addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance()
      .addHeader("Access-Control-Allow-Methods", "GET, POST, PUT");
  DefaultHeaders::Instance()
      .addHeader("Access-Control-Allow-Headers", "Content-Type");

  while (true)
  {

    // if it's not transitioning modes
    if (NETWORK_STATE.getWiFiState() != TRANSITIONING)
    {
      switch (NETWORK_STATE.getWiFiMode())
      {
      case AP_MODE: /* In AP mode, just process the dns requests */
        dnsServer.processNextRequest();
        /* code */
        break;

      case STA_MODE:
        /* code */
        // Serial.println(NETWORK_STATE.isConnected());
        break;

      case IDLE:
        // Do nothing, idle state...
        break;
      }
    }
    else
    {
      handleModeTransitioning(LastWiFiMode, NETWORK_STATE, captivePortal, controlPanel, api, dnsServer);
    }
    vTaskDelay(pdMS_TO_TICKS(30));
  }
}

// void ap()
// {
//   // if (xSemaphoreTake(wMutex, portMAX_DELAY) == pdTRUE)
//   // {
//   WiFi.disconnect();
//   WiFi.mode(WIFI_AP);
//   // WiFi.softAP(networkConfig.INTERNALSSID, networkConfig.INTERNALPASS);
//   //     xSemaphoreGive(wMutex);
//   // }
// }

// void attachUDPListeners()
// {
// if (xSemaphoreTake(wMutex, portMAX_DELAY) == pdTRUE)
// {
// server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
// {
// Serial.println(request->args());
// //AsyncWebServerResponse *response = request->beginResponse(HTTP_STATUS_SERVICE_UNAVAILABLE);
// AsyncWebServerResponse *response = request->beginResponse(HTTP_STATUS_OK, "application/json", "{'response': 'ok'}");
// // AsyncWebServerResponse *response = request->beginResponse(HTTP_STATUS_SERVICE_UNAVAILABLE, "application/json",
// "{'response':'ok'}");
// response->addHeader("Server", "ESP Async Web Server");
// request->send(response); });

// if (udp.listenMulticast(networkConfig.MCASTGROUP, networkConfig.MCASTPORT))
// {
// Serial.print("UDP Multicast Listener started at: ");
// Serial.println(networkConfig.MCASTGROUP);
// udp.onPacket([](AsyncUDPPacket packet)
// {
// Serial.print("UDP packet received from ");
// Serial.print(packet.remoteIP());
// Serial.print(":");
// Serial.print(packet.remotePort());
// Serial.print(", type: ");
// Serial.print(packet.isBroadcast() ? "Broadcast" : (packet.isMulticast() ? "Multicast" : "Normal Packet"));
// Serial.print(", size: ");
// Serial.print(packet.length());
// Serial.print(", data: ");
// Serial.println((char *)packet.data());
// // udp.print("Received!");
// });
// }
// else
// {
// Serial.println("Failed to initialize UDP listener.");
// }

// server.begin();
// }
// }
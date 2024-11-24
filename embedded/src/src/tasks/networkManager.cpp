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
  setUpDNSServer(dnsServer);
  setUpCaptivePortalServer(captivePortal);
  setUpAPIServer(api);

  NETWORK_STATE.setWiFiMode(AP_MODE);

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
      Serial.println("Está no estado operacional");
      switch (NETWORK_STATE.getWiFiMode())
      {
      case AP_MODE: /* In AP mode, just process the dns requests */

        Serial.println("modo AP");
        dnsServer.processNextRequest();
        /* code */
        break;

      case STA_MODE:
        Serial.println("modo STA");
        /* code */
        break;

      case IDLE:
        // Do nothing, idle state...
        break;
      }
    }
    else
    {
      Serial.println("entrou no modo de transição");
      handleModeTransitioning(LastWiFiMode, NETWORK_STATE, captivePortal, controlPanel, api, dnsServer);
    }
    vTaskDelay(pdMS_TO_TICKS(30));
  }
}

// wl_status_t connect(u8_t tries = 25, u16_t delay = 250)
// {
//   SEMAPHORE_WRAPPER(networkOperationsMutex, {
//     WiFi.mode(WIFI_STA);
//     WiFi.disconnect();

//     // WiFi.begin(networkConfig.SSID, networkConfig.PASS);

//     u8_t count = 0;
//     do
//     {
//       vTaskDelay(pdMS_TO_TICKS(delay));
//       count++;
//     } while ((WiFi.status() != WL_CONNECTED) && (count < tries));
//   });

//   return WiFi.status();
// }

// wl_status_t disconnect()
// {
//   SEMAPHORE_WRAPPER(networkOperationsMutex, { WiFi.disconnect(); });
//   return WiFi.status();
// }

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
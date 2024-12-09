#include <src/tasks/networkManager.h>

// DNS server
DNSServer dnsServer;

// Webservers
AsyncWebServer captivePortal(80);
AsyncWebServer controlPanel(80);
AsyncWebServer api(9000);
AsyncWebSocket ws("/ws");

// Local state storing
WiFiMode LastWiFiMode = IDLE;
WiFiState LastWiFiState = OFF;

long lastTime = 0;

void networkManager(void *pvParameters)
{
  disconnect(AP_MODE);
  disconnect(STA_MODE);

  setUpDNSServer(dnsServer);
  setUpCaptivePortalServer(captivePortal);
  setUpAPIServer(api);

  // NETWORK_STATE.setWiFiMode(STA_MODE);
  NETWORK_STATE.setWiFiMode(AP_MODE);

  /* Default headers */
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization");

  while (true)
  {

    // if it's not transitioning modes
    if (NETWORK_STATE.getWiFiState() != TRANSITIONING)
    {
      switch (NETWORK_STATE.getWiFiMode())
      {
      case AP_MODE: /* In AP mode, just process the dns requests */

        if ((millis() - lastTime) > WEBSOCKET_REFRESH_RATE)
        {
          handleWebSocket(ws);
          lastTime = millis();
        }

        dnsServer.processNextRequest();
        ws.cleanupClients();
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
      handleModeTransitioning(LastWiFiMode, NETWORK_STATE, captivePortal, controlPanel, api, dnsServer, ws);
    }
    vTaskDelay(pdMS_TO_TICKS(30));
  }
}
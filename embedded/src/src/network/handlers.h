#ifndef HANDLERS_H
#define HANDLERS_H

#include <src/data/data.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <esp_wifi.h>
#include <src/data/macros.h>
#include <src/network/request_middleware.h>
#include <src/data/database.h>
#include <src/data/queries/defaults.h>
#include <map>

#define filesystem APPLICATION_STATE.filesystem
#define noBodyRequestHandler [](AsyncWebServerRequest *request) { request->send(401); }

// Modular API endpoint macro
#define ATTACHROUTE(route, server, code)                                                                \
    server.on(route, HTTP_POST, noBodyRequestHandler, nullptr,                                          \
              [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) \
              {                                                                                         \
                  if (!validateRequest(request, data, len))                                             \
                  {                                                                                     \
                      Serial.println(validateRequest(request, data, len));                              \
                      request->send(401);                                                               \
                      return;                                                                           \
                  }                                                                                     \
                                                                                                        \
                  JsonDocument requestBody;                                                             \
                  DeserializationError error = deserializeJson(requestBody, data, len);                 \
                  if (error)                                                                            \
                  {                                                                                     \
                      request->send(400, "application/json", "{\"error\":\"Invalid JSON\"}");           \
                      return;                                                                           \
                  }                                                                                     \
                                                                                                        \
                  {                                                                                     \
                      code                                                                              \
                  }                                                                                     \
              });

#define KEYVERIFICATION(key, dataType)    \
    if (!requestBody[key].is<dataType>()) \
    {                                     \
        request->send(400);               \
        return;                           \
    }

#define MAX_CLIENTS 4
#define WIFI_CHANNEL 6

void handleModeTransitioning(WiFiMode &lastMode,
                             NetworkState &netState,
                             AsyncWebServer &captivePortal,
                             AsyncWebServer &controlPanel,
                             AsyncWebServer &api,
                             DNSServer &dnsServer,
                             AsyncWebSocket &webSocket);

void toggleHandlers(ONOFF action,
                    WiFiMode mode,
                    AsyncWebServer &captivePortal,
                    AsyncWebServer &controlPanel,
                    AsyncWebServer &api,
                    DNSServer &dnsServer,
                    AsyncWebSocket &ws,
                    const IPAddress &localIp);

extern String gatherUpdatedData(void);
extern void setUpDNSServer(DNSServer &server);
extern void setUpAPIServer(AsyncWebServer &server);
extern void setUpCaptivePortalServer(AsyncWebServer &server);
extern void startSoftAccessPoint(const char *ssid, const char *password, const IPAddress &localIP, const IPAddress &gatewayIP, const IPAddress &subnetMask);
extern void notifyClients(AsyncWebSocket &ws, String message);
extern void handleWebSocket(AsyncWebSocket &ws);
// extern void handleWebSocketMessage(AsyncWebSocket *ws, void *arg, uint8_t *data, size_t len);
extern void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

wl_status_t connect(String ssid, String password, u8_t tries, u16_t delay);
extern wl_status_t disconnect(WiFiMode mode);

#endif
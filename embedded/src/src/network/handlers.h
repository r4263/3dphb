#ifndef HANDLERS_H
#define HANDLERS_H

#include <src/data/data.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <esp_wifi.h>
#include <src/data/macros.h>

#define filesystem APPLICATION_STATE.filesystem

#define MAX_CLIENTS 4
#define WIFI_CHANNEL 6

extern void handleModeTransitioning(WiFiMode &lastMode,
                                    NetworkState &netState,
                                    AsyncWebServer &captivePortal,
                                    AsyncWebServer &controlPanel,
                                    AsyncWebServer &api,
                                    DNSServer &dnsServer);

extern void toggleHandlers(ONOFF action,
                           WiFiMode mode,
                           AsyncWebServer &captivePortal,
                           AsyncWebServer &controlPanel,
                           AsyncWebServer &api,
                           DNSServer &dnsServer,
                           const IPAddress &localIp);

extern void setUpDNSServer(DNSServer &server);
extern void setUpAPIServer(AsyncWebServer &server);
extern void setUpCaptivePortalServer(AsyncWebServer &server);
extern void startSoftAccessPoint(const char *ssid, const char *password, const IPAddress &localIP, const IPAddress &gatewayIP, const IPAddress &subnetMask);

wl_status_t connect(String ssid, String password, u8_t tries, u16_t delay);
extern wl_status_t disconnect(WiFiMode mode);

#endif
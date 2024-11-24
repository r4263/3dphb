#ifndef HANDLERS_H
#define HANDLERS_H

#include <src/data/data.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <esp_wifi.h>

#define MAX_CLIENTS 4
#define WIFI_CHANNEL 6

#define filesystem APPLICATION_STATE.filesystem

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

#endif
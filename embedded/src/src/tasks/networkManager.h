#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// #include <AsyncUDP.h>
#include <src/wTools.h>
// #include <src/data/macros.h>
#include <src/data/data.h>
#include <DNSServer.h>
#include <esp_wifi.h>
#include <src/network/handlers.h>
#include <src/data/filetools.h>

#define filesystem APPLICATION_STATE.filesystem

extern void networkManager(void *pvParameters);
// extern void ap();
// extern wl_status_t connect(u8_t tries, u16_t delay);
// extern wl_status_t disconnect();
// extern void attachUDPListeners();

// extern void setUpDNSServer(DNSServer &dnsServer, const IPAddress &localIP);
// extern void startSoftAccessPoint(const char *ssid, const char *password, const IPAddress &localIP, const IPAddress &gatewayIP);
// extern void setUpWebserver(AsyncWebServer &server, const IPAddress &localIP);

#endif
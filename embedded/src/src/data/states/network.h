#ifndef NETWORKSTATE_H
#define NETWORKSTATE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <src/data/macros.h>
#include <src/data/identifiers.h>
#include <src/data/types.h>

typedef struct
{
    WiFiMode wifi_mode = IDLE;
    WiFiState wifi_state = OFF;
    uint16_t wifi_scan_interval;
    String ap_ssid;
    String ap_pwk;
    String sta_ssid;
    String sta_pwk;
    IPAddress multicast_group;
    uint16_t multicast_port;
    String scan_result;

    // Functionalities setters
    void setNetworkScanResult(String networks);
    void setNetworkScanInterval(uint16_t time);
    void setWiFiMode(WiFiMode mode);
    void setWiFiState(WiFiState mode);

    // Functionalities getters
    String getNetworkScanResult(void);
    uint16_t getNetworkScanInterval(void);
    WiFiMode getWiFiMode(void);
    WiFiState getWiFiState(void);

    // Connection properties setters
    void setAPSSID(String ssid);
    void setAPPWK(String pass);
    void setSTASSID(String ssid);
    void setSTAPWK(String pass);

    // Connection properties getters
    String getAPSSID(void);
    String getAPPWK(void);
    String getSTASSID(void);
    String getSTAPWK(void);

} NetworkState;

#endif
#include <src/wTools.h>

String ssidTreatment(String ssid)
{
    if (ssid == "")
    {
        return "HIDDEN NETWORK";
    }
    return ssid;
}

String authModeStr(wifi_auth_mode_t encodingType)
{
    switch (encodingType)
    {
    case WIFI_AUTH_OPEN:
        return "OPEN";
    case WIFI_AUTH_WEP:
        return "WEP";
    case WIFI_AUTH_WPA_PSK:
        return "WPA";
    case WIFI_AUTH_WPA2_PSK:
        return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK:
        return "WPA+WPA2";
    case WIFI_AUTH_WPA2_ENTERPRISE:
        return "WPA2-EAP";
    case WIFI_AUTH_WPA3_PSK:
        return "WPA3";
    case WIFI_AUTH_WPA2_WPA3_PSK:
        return "WPA2+WPA3";
    case WIFI_AUTH_WAPI_PSK:
        return "WAPI";
    default:
        return "UNKNOWN";
    }
}

String getNearbyNetworks()
{
    String networks, nwStr;
    JsonDocument doc;
    JsonObject network = doc.to<JsonObject>();

    int n = WiFi.scanNetworks(false, true);

    for (int i = 0; i < n; ++i)
    {
        network["SSID"] = ssidTreatment(WiFi.SSID(i));
        network["RSSI"] = WiFi.RSSI(i);
        network["CHANNEL"] = WiFi.channel(i);
        network["ENCTYPE"] = authModeStr(WiFi.encryptionType(i));
        network["MACADDR"] = WiFi.BSSIDstr(i).c_str();

        serializeJson(doc, nwStr);
        networks += nwStr;
    }

    WiFi.scanDelete();
    return networks;
}
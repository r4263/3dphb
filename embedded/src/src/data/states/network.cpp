#include <src/data/states/network.h>

void NetworkState::setWiFiMode(WiFiMode mode)
{
    SEMAPHORE_WRAPPER(networkStateMutex, {
        this->wifi_mode = mode;
        this->wifi_state = TRANSITIONING;
    });
}

void NetworkState::setWiFiState(WiFiState state)
{
    SEMAPHORE_WRAPPER(networkStateMutex, { this->wifi_state = state; });
}

// Functionalities getters
WiFiMode NetworkState::getWiFiMode(void)
{
    WiFiMode mode = IDLE;
    SEMAPHORE_WRAPPER(networkStateMutex, { mode = this->wifi_mode; });

    return mode;
}

WiFiState NetworkState::getWiFiState(void)
{
    WiFiState state = OFF;
    SEMAPHORE_WRAPPER(networkStateMutex, { state = this->wifi_state; });

    return state;
}

void NetworkState::setNetworkScanResult(String networks)
{
    SEMAPHORE_WRAPPER(networkStateMutex, { this->scan_result = networks; });
}

void NetworkState::setNetworkScanInterval(uint16_t time)
{
    SEMAPHORE_WRAPPER(networkStateMutex, { this->wifi_scan_interval = time; });
}

String NetworkState::getNetworkScanResult(void)
{
    String networks;
    SEMAPHORE_WRAPPER(networkStateMutex, { networks = this->scan_result; });

    return networks;
}

// Connection properties setters,
uint16_t NetworkState::getNetworkScanInterval(void)
{
    uint16_t interval;
    SEMAPHORE_WRAPPER(networkStateMutex, { interval = this->wifi_scan_interval; });

    return interval;
}

// Connection properties setters
void NetworkState::setAPSSID(String ssid)
{
    SEMAPHORE_WRAPPER(networkStateMutex, { this->ap_ssid = ssid; });
}

void NetworkState::setAPPWK(String pass)
{
    SEMAPHORE_WRAPPER(networkStateMutex, { this->ap_pwk = pass; });
}

void NetworkState::setSTASSID(String ssid)
{
    SEMAPHORE_WRAPPER(networkStateMutex, { this->sta_ssid = ssid; });
}

void NetworkState::setSTAPWK(String pass)
{
    SEMAPHORE_WRAPPER(networkStateMutex, { this->sta_pwk = pass; });
}

// Connection properties getters
String NetworkState::getAPSSID(void)
{
    String ssid;
    SEMAPHORE_WRAPPER(networkStateMutex, { ssid = this->ap_ssid; });

    return ssid;
}

String NetworkState::getAPPWK(void)
{
    String pass;
    SEMAPHORE_WRAPPER(networkStateMutex, { pass = this->ap_pwk; });

    return pass;
}

String NetworkState::getSTASSID(void)
{
    String ssid;
    SEMAPHORE_WRAPPER(networkStateMutex, { ssid = this->sta_ssid; });

    return ssid;
}

String NetworkState::getSTAPWK(void)
{
    String pass;
    SEMAPHORE_WRAPPER(networkStateMutex, { pass = this->sta_pwk; });

    return pass;
}

void NetworkState::connected(boolean state)
{
    SEMAPHORE_WRAPPER(networkStateMutex, { this->wifi_sta_is_connected = state; });
}

boolean NetworkState::isConnected(void)
{
    boolean state;
    SEMAPHORE_WRAPPER(networkStateMutex, { state = this->wifi_sta_is_connected; });

    return state;
}
#include <src/network/handlers.h>

const IPAddress localIP(4, 4, 4, 1);
const IPAddress gatewayIP(4, 4, 4, 1);
const IPAddress subnetMask(255, 255, 255, 0);

const String localIPURL = "http://" + localIP.toString();

const char *ssid = "phb-ctrl";
const char *password = NULL;

/**
 * Handler to transition states between wifi modes
 */
void handleModeTransitioning(WiFiMode &lastMode,
                             NetworkState &netState,
                             AsyncWebServer &captivePortal,
                             AsyncWebServer &controlPanel,
                             AsyncWebServer &api,
                             DNSServer &dnsServer)
{

    WiFiMode currentMode = netState.getWiFiMode(); // The state access can be used directly during the code, but to avoid any kind of problem related as multitasking conflict during the execution, made it fixed here

    switch (currentMode)
    {
    case IDLE: /* if it goes to IDLE mode, turn all off */
        toggleHandlers(off, lastMode, captivePortal, controlPanel, api, dnsServer, localIP);
        api.end(); // Shared between the AP and STA modes

        WiFi.mode(WIFI_OFF);        /* Turn WiFi off to reduce consumption and relief CPU resources */
        netState.setWiFiState(OFF); /* Set the global state to off, just a convention to use it all over the code */
        lastMode = IDLE;
        break;

    default: /* If it's not to go to idle mode */

        /**
         * Turn off all servers that won't be used in the new mode
         * if the code is reaching this point, it assumes that is
         * already validated and will just switch between the remaining modes
         * obs: the remaining modes share the api server
         */
        toggleHandlers(off, lastMode, captivePortal, controlPanel, api, dnsServer, localIP);

        // Turn WiFi on
        // if (WiFi.getMode() != WIFI_AP_STA)
        //     WiFi.mode(WIFI_AP_STA);

        // Disconnects from the last mode informed
        if (WiFi.getMode() != WIFI_OFF)
            disconnect(lastMode);

        switch (currentMode)
        {
        case AP_MODE:
            WiFi.mode(WIFI_AP);
            Serial.println("AP MODE INIT");
            startSoftAccessPoint(ssid, password, localIP, gatewayIP, subnetMask);
            break;

        case STA_MODE:
            WiFi.mode(WIFI_STA);
            Serial.println("STA MODE INIT");
            netState.connected(connect(netState.getSTASSID(), netState.getSTAPWK(), 25, 250) == WL_CONNECTED);
            break;
        }

        // Toggle the handlers on
        toggleHandlers(on, currentMode, captivePortal, controlPanel, api, dnsServer, localIP);

        netState.setWiFiState(OPERATIONAL);
        lastMode = (WiFiMode)currentMode; // Casting, trying not to pass direct memory reference that could mess it all
        break;
    }
}

void setUpAPIServer(AsyncWebServer &server)
{
    ATTACHROUTE("/state/get", server, {
        JsonDocument jsonResponse;

        jsonResponse["kp"] = APPLICATION_STATE.getKp();
        jsonResponse["ki"] = APPLICATION_STATE.getKi();
        jsonResponse["kd"] = APPLICATION_STATE.getKd();
        jsonResponse["setpoint"] = APPLICATION_STATE.getSetpoint();
        jsonResponse["bed_temp"] = APPLICATION_STATE.getBedTemperature();
        jsonResponse["cpu_temp"] = APPLICATION_STATE.getCPUTemperature();
        jsonResponse["heater_enabled"] = APPLICATION_STATE.getOutputState();

        String serializedResponse;
        serializeJson(jsonResponse, serializedResponse);

        request->send(200, "application/json", serializedResponse);
    });

    ATTACHROUTE("/state/set/setpoint", server, {
        // if there's no setpoint key or is not float, return Bad request
        KEYVERIFICATION("setpoint", int);

        // Saving to the application state, cast to double to prevent errors
        APPLICATION_STATE.setSetpoint(requestBody["setpoint"].as<double>());

        request->send(200);
    });

    ATTACHROUTE("/state/set/kp", server, {
        // if there's no kp key or is not float, return Bad request
        KEYVERIFICATION("kp", float);

        double kp = requestBody["kp"].as<double>();
        APPLICATION_STATE.setKp(kp);

        if (!requestBody["volatile"].as<bool>())
        {
            queryDatabase(("UPDATE configs SET kp = " + String(kp, 3) + ";").c_str(), false);
        }

        request->send(200);
    });

    ATTACHROUTE("/state/set/ki", server, {
        // if there's no ki key or is not float, return Bad request
        KEYVERIFICATION("ki", float);

        double ki = requestBody["ki"].as<double>();
        APPLICATION_STATE.setKp(ki);

        if (!requestBody["volatile"].as<bool>())
        {
            queryDatabase(("UPDATE configs SET ki = " + String(ki, 6) + ";").c_str(), false);
        }

        request->send(200);
    });

    ATTACHROUTE("/state/set/kd", server, {
        // if there's no kd key or is not float, return Bad request
        KEYVERIFICATION("kd", float);

        double kd = requestBody["kd"].as<double>();
        APPLICATION_STATE.setKp(kd);

        if (!requestBody["volatile"].as<bool>())
        {
            queryDatabase(("UPDATE configs SET kd = " + String(kd, 3) + ";").c_str(), false);
        }

        request->send(200);
    });

    ATTACHROUTE("/state/heater", server, {
        // if there's no heater_enabled key or is not bool, return Bad request
        KEYVERIFICATION("heater_enable", float);

        request->send(200);
    });

    server.onNotFound([](AsyncWebServerRequest *request)
                      { request->send(401); });
}

void setUpCaptivePortalServer(AsyncWebServer &server)
{
    server.on("/204*", [](AsyncWebServerRequest *request)
              { request->send(404); });

    server.on("/connecttest.txt", [](AsyncWebServerRequest *request)
              { request->redirect("http://logout.net"); });
    server.on("/wpad.dat", [](AsyncWebServerRequest *request)
              { request->send(404); });

    server.on("/generate_204", [](AsyncWebServerRequest *request)
              { request->redirect(localIPURL); });
    server.on("/redirect", [](AsyncWebServerRequest *request)
              { request->redirect(localIPURL); });
    server.on("/hotspot-detect.html", [](AsyncWebServerRequest *request)
              { request->redirect(localIPURL); });
    server.on("/canonical.html", [](AsyncWebServerRequest *request)
              { request->redirect(localIPURL); });
    server.on("/success.txt", [](AsyncWebServerRequest *request)
              { request->send(200); });
    server.on("/ncsi.txt", [](AsyncWebServerRequest *request)
              { request->redirect(localIPURL); });

    server.on("/chrome-variations/seed", [](AsyncWebServerRequest *request)
              { request->send(200); });
    server.on("/service/update2/json", [](AsyncWebServerRequest *request)
              { request->send(200); });
    server.on("/chat", [](AsyncWebServerRequest *request)
              { request->send(404); });
    server.on("/startpage", [](AsyncWebServerRequest *request)
              { request->redirect(localIPURL); });

    server.on("/favicon.ico", [](AsyncWebServerRequest *request)
              { request->send(404); }); // webpage icon

    server.serveStatic("/", filesystem, "/web/portal/").setDefaultFile("index.html");
    server.serveStatic("/static/", filesystem, "/web/portal/static");

    server.onNotFound([](AsyncWebServerRequest *request)
                      { request->redirect(localIPURL); });
}

void setUpDNSServer(DNSServer &dnsServer)
{
    // dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.setTTL(3600);
}

void toggleHandlers(ONOFF action,
                    WiFiMode mode,
                    AsyncWebServer &captivePortal,
                    AsyncWebServer &controlPanel,
                    AsyncWebServer &api,
                    DNSServer &dnsServer,
                    const IPAddress &localIp)
{
    if (action)
    {
        switch (mode)
        {
        case AP_MODE:
            captivePortal.begin();
            dnsServer.start(53, "*", localIp);
            break;

        case STA_MODE:
            controlPanel.begin();
            // --> UDP Listener server here <--
            break;
        }
        api.begin();
    }
    else
    {
        switch (mode)
        {
        case AP_MODE:
            captivePortal.end();
            dnsServer.stop();
            break;

        case STA_MODE:
            controlPanel.end();
            // --> UDP Listener server here <--
            break;
        }
    }
}

void startSoftAccessPoint(const char *ssid, const char *password, const IPAddress &localIP, const IPAddress &gatewayIP, const IPAddress &subnetMask)
{
    WiFi.softAPConfig(localIP, gatewayIP, subnetMask);

    WiFi.softAP(ssid, password, WIFI_CHANNEL, 0, MAX_CLIENTS);

    // esp_wifi_stop();
    // esp_wifi_deinit();
    // wifi_init_config_t my_config = WIFI_INIT_CONFIG_DEFAULT();
    // my_config.ampdu_rx_enable = false;
    // esp_wifi_init(&my_config);
    // esp_wifi_start();
    vTaskDelay(100 / portTICK_PERIOD_MS);
}

wl_status_t connect(String ssid, String password, u8_t tries, u16_t delay)
{
    WiFi.disconnect();

    WiFi.begin(ssid, password);

    u8_t count = 0;
    do
    {
        vTaskDelay(pdMS_TO_TICKS(delay));
        count++;
    } while ((WiFi.status() != WL_CONNECTED) && (count < tries));

    return WiFi.status();
}

wl_status_t disconnect(WiFiMode mode)
{
    if (mode == AP_MODE)
        WiFi.softAPdisconnect(true);
    else
        WiFi.disconnect();
    return WiFi.status();
}
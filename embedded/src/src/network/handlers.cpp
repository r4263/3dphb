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
        switch (lastMode)
        {
        case AP_MODE: /* Turn API server, DNS server and captive portal off */
            Serial.println("Turn off AP mode");
            captivePortal.end();
            dnsServer.stop();
            break;

        case STA_MODE: /* Turn control panel, API server and UDP listener off */
            Serial.println("Turn off STA mode");
            controlPanel.end();
            // --> UDP Listener server here <--
            break;
        }

        api.end(); // Shared between the AP and STA modes

        WiFi.mode(WIFI_OFF);        /* Turn WiFi off to reduce consumption and relief CPU resources */
        netState.setWiFiState(OFF); /* Set the global state to off, just a convention to use it all over the code */
        lastMode = IDLE;
        break;

    default: /* If it's not to go to idle mode */

        Serial.println("Turning on...");

        /**
         * Turn off all servers that won't be used in the new mode
         * if the code is reaching this point, it assumes that is
         * already validated and will just switch between the remaining modes
         * obs: the remaining modes share the api server
         */
        toggleHandlers(off, lastMode, captivePortal, controlPanel, api, dnsServer, localIP);

        if (WiFi.getMode() != WIFI_AP_STA)
            WiFi.mode(WIFI_AP_STA);

        // Turn WiFi on
        Serial.println("Turning wifi on");
        switch (currentMode)
        {
        case AP_MODE:
            if (WiFi.getMode() != WIFI_OFF)
                WiFi.disconnect();

            Serial.println("Turning on softap");
            startSoftAccessPoint(ssid, password, localIP, gatewayIP, subnetMask);
            Serial.println(ssid);
            Serial.println(password);

            break;

        case STA_MODE:
            if (WiFi.getMode() != WIFI_OFF)
                WiFi.softAPdisconnect();

            Serial.println("Turning on sta");
            WiFi.begin(netState.getSTASSID(), netState.getAPPWK());
            break;
        }

        // Toggle the handlers on
        toggleHandlers(on, currentMode, captivePortal, controlPanel, api, dnsServer, localIP);

        Serial.println(WiFi.getMode());
        Serial.println(WiFi.getHostname());

        netState.setWiFiState(OPERATIONAL);
        lastMode = (WiFiMode)currentMode; // Casting, trying not to pass direct memory reference that could mess it all
        Serial.println("Passed");
        break;
    }
}

void setUpAPIServer(AsyncWebServer &server)
{
    server.on("/teste", HTTP_POST, [](AsyncWebServerRequest *request)
              {

				IPAddress clientIP = request->client()->remoteIP();

				String res = "{/""mac/"":""/"+clientIP.toString()+"/""}";

				request->send(200, "application/json", res); });

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
                    const IPAddress &localIp) // Use const IPAddress&
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
    WiFi.mode(WIFI_MODE_AP);

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

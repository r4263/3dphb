#include <src/network/handlers.h>

const IPAddress localIP(4, 4, 4, 1);
const IPAddress gatewayIP(4, 4, 4, 1);
const IPAddress subnetMask(255, 255, 255, 0);

const String localIPURL = "http://" + localIP.toString();

const char *ssid = "phb-ctrl";
const char *password = NULL;

std::map<String, double> previousState;

/**
 * Handler to transition states between wifi modes
 */
void handleModeTransitioning(WiFiMode &lastMode,
                             NetworkState &netState,
                             AsyncWebServer &captivePortal,
                             AsyncWebServer &controlPanel,
                             AsyncWebServer &api,
                             DNSServer &dnsServer,
                             AsyncWebSocket &webSocket)
{
    WiFiMode currentMode = netState.getWiFiMode();

    switch (currentMode)
    {
    case IDLE: // Turn everything off
        toggleHandlers(off, lastMode, captivePortal, controlPanel, api, dnsServer, webSocket, localIP);
        api.end();

        WiFi.mode(WIFI_OFF);
        netState.setWiFiState(OFF);
        lastMode = IDLE;
        break;

    default:
        toggleHandlers(off, lastMode, captivePortal, controlPanel, api, dnsServer, webSocket, localIP);

        if (WiFi.getMode() != WIFI_OFF)
            disconnect(lastMode);

        switch (currentMode)
        {
        case AP_MODE:
            WiFi.mode(WIFI_AP);
            startSoftAccessPoint(ssid, password, localIP, gatewayIP, subnetMask);
            break;

        case STA_MODE:
            WiFi.mode(WIFI_STA);
            netState.connected(connect(netState.getSTASSID(), netState.getSTAPWK(), 25, 250) == WL_CONNECTED);
            break;
        }

        toggleHandlers(on, currentMode, captivePortal, controlPanel, api, dnsServer, webSocket, localIP);

        netState.setWiFiState(OPERATIONAL);
        lastMode = currentMode;
        break;
    }
}

// handler for getting only the updated data to send for the websocket connected client
String gatherUpdatedData(void)
{
    JsonDocument jsonResponse;
    bool hasUpdates = false;

    if (APPLICATION_STATE.getKp() != previousState["kp"])
    {
        jsonResponse["kp"] = APPLICATION_STATE.getKp();
        previousState["kp"] = APPLICATION_STATE.getKp();
        hasUpdates = true;
    }

    if (APPLICATION_STATE.getKi() != previousState["ki"])
    {
        jsonResponse["ki"] = APPLICATION_STATE.getKi();
        previousState["ki"] = APPLICATION_STATE.getKi();
        hasUpdates = true;
    }

    if (APPLICATION_STATE.getKd() != previousState["kd"])
    {
        jsonResponse["kd"] = APPLICATION_STATE.getKd();
        previousState["kd"] = APPLICATION_STATE.getKd();
        hasUpdates = true;
    }

    if (APPLICATION_STATE.getSetpoint() != previousState["setpoint"])
    {
        jsonResponse["setpoint"] = APPLICATION_STATE.getSetpoint();
        previousState["setpoint"] = APPLICATION_STATE.getSetpoint();
        hasUpdates = true;
    }

    if (APPLICATION_STATE.getBedTemperature() != previousState["bed_temp"])
    {
        jsonResponse["bed_temp"] = APPLICATION_STATE.getBedTemperature();
        previousState["bed_temp"] = APPLICATION_STATE.getBedTemperature();
        hasUpdates = true;
    }

    if (APPLICATION_STATE.getCPUTemperature() != previousState["cpu_temp"])
    {
        jsonResponse["cpu_temp"] = APPLICATION_STATE.getCPUTemperature();
        previousState["cpu_temp"] = APPLICATION_STATE.getCPUTemperature();
        hasUpdates = true;
    }

    if (APPLICATION_STATE.getControlMode() != previousState["control_mode"])
    {
        jsonResponse["control_mode"] = APPLICATION_STATE.getControlMode();
        previousState["control_mode"] = APPLICATION_STATE.getControlMode();
        hasUpdates = true;
    }

    if (APPLICATION_STATE.getOutputState() != previousState["heater_enabled"])
    {
        jsonResponse["heater_enabled"] = APPLICATION_STATE.getOutputState();
        previousState["heater_enabled"] = APPLICATION_STATE.getOutputState();
        hasUpdates = true;
    }

    if (APPLICATION_STATE.getLowerHysteresisValue() != previousState["lh"])
    {
        jsonResponse["lh"] = APPLICATION_STATE.getLowerHysteresisValue();
        previousState["lh"] = APPLICATION_STATE.getLowerHysteresisValue();
        hasUpdates = true;
    }

    if (APPLICATION_STATE.getUpperHysteresisValue() != previousState["hh"])
    {
        jsonResponse["hh"] = APPLICATION_STATE.getUpperHysteresisValue();
        previousState["hh"] = APPLICATION_STATE.getUpperHysteresisValue();
        hasUpdates = true;
    }

    if (!hasUpdates)
    {
        return "";
    }

    String serializedResponse;
    serializeJson(jsonResponse, serializedResponse);

    return serializedResponse;
}

String gatherSystemData()
{
    JsonDocument jsonResponse;

    jsonResponse["kp"] = APPLICATION_STATE.getKp();
    jsonResponse["ki"] = APPLICATION_STATE.getKi();
    jsonResponse["kd"] = APPLICATION_STATE.getKd();
    jsonResponse["setpoint"] = APPLICATION_STATE.getSetpoint();
    jsonResponse["bed_temp"] = APPLICATION_STATE.getBedTemperature();
    jsonResponse["cpu_temp"] = APPLICATION_STATE.getCPUTemperature();
    jsonResponse["heater_enabled"] = APPLICATION_STATE.getOutputState();
    jsonResponse["control_mode"] = APPLICATION_STATE.getControlMode();
    jsonResponse["lh"] = APPLICATION_STATE.getLowerHysteresisValue();
    jsonResponse["hh"] = APPLICATION_STATE.getUpperHysteresisValue();

    String serializedResponse;
    serializeJson(jsonResponse, serializedResponse);

    return serializedResponse;
}

void setUpAPIServer(AsyncWebServer &server)
{
    server.on("*", HTTP_OPTIONS, [](AsyncWebServerRequest *request)
              { request->send(204); });

    ATTACHROUTE("/state/get", server, {
        request->send(200, "application/json", gatherSystemData());
    });

    ATTACHROUTE("/state/set/setpoint", server, {
        KEYVERIFICATION("setpoint", int);
        double sp = requestBody["setpoint"].as<double>();

        APPLICATION_STATE.setSetpoint(sp);

        updateDatabase("setpoint", String(sp));

        request->send(200);
    });

    ATTACHROUTE("/state/set/control", server, {
        KEYVERIFICATION("mode", float);
        uint8_t mode = requestBody["mode"].as<uint8_t>();
        APPLICATION_STATE.setControlMode((ControlModes)mode);

        updateDatabase("control_mode", String(mode));

        request->send(200);
    });

    ATTACHROUTE("/state/set/hh", server, {
        KEYVERIFICATION("hh", int);
        uint8_t hh = requestBody["hh"].as<uint8_t>();

        APPLICATION_STATE.setUpperHysteresisValue(hh);

        updateDatabase("hh", String(hh));

        request->send(200);
    });

    ATTACHROUTE("/state/set/lh", server, {
        KEYVERIFICATION("lh", int);
        uint8_t lh = requestBody["lh"].as<uint8_t>();

        APPLICATION_STATE.setLowerHysteresisValue(lh);

        updateDatabase("lh", String(lh));

        request->send(200);
    });

    ATTACHROUTE("/state/set/kp", server, {
        KEYVERIFICATION("kp", float);
        double kp = requestBody["kp"].as<double>();
        APPLICATION_STATE.setKp(kp);

        if (!requestBody["volatile"].as<bool>())
        {
            updateDatabase("kp", String(kp));
        }

        request->send(200);
    });

    ATTACHROUTE("/state/set/ki", server, {
        KEYVERIFICATION("ki", float);
        double ki = requestBody["ki"].as<double>();
        APPLICATION_STATE.setKi(ki);

        if (!requestBody["volatile"].as<bool>())
        {
            updateDatabase("ki", String(ki));
        }

        request->send(200);
    });

    ATTACHROUTE("/state/set/kd", server, {
        KEYVERIFICATION("kd", float);
        double kd = requestBody["kd"].as<double>();
        APPLICATION_STATE.setKd(kd);

        if (!requestBody["volatile"].as<bool>())
        {
            updateDatabase("kd", String(kd));
        }

        request->send(200);
    });

    ATTACHROUTE("/state/set/heater", server, {
        KEYVERIFICATION("heater_enable", bool);
        bool he = requestBody["heater_enable"].as<bool>();

        he ? APPLICATION_STATE.enableOutput() : APPLICATION_STATE.disableOutput();

        request->send(200);
    });

    server.onNotFound([](AsyncWebServerRequest *request)
                      { 
        if (request->method() == HTTP_OPTIONS) {
            request->send(204); // Handling CORS preflight, Cross Platform API consuming
        } else {
            request->send(401);
        } });
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

    server.serveStatic("/", filesystem, "/web/panel/").setDefaultFile("index.html");
    server.serveStatic("/static/", filesystem, "/web/panel/static");
    // server.serveStatic("/", filesystem, "/web/portal/").setDefaultFile("index.html");
    // server.serveStatic("/static/", filesystem, "/web/portal/static");

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
                    AsyncWebSocket &ws,
                    const IPAddress &localIp)
{
    if (action)
    {
        switch (mode)
        {
        case AP_MODE:
            ws.onEvent(onEvent);
            captivePortal.addHandler(&ws);
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
            captivePortal.removeHandler(&ws);
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

void handleWebSocket(AsyncWebSocket &ws)
{
    String updatedData = gatherUpdatedData();

    if (!updatedData.isEmpty())
    {
        notifyClients(ws, updatedData);
    }
}

void notifyClients(AsyncWebSocket &ws, String message)
{
    ws.textAll(message);
}

void handleWebSocketMessage(AsyncWebSocket &ws, void *arg, uint8_t *data, size_t len)
{
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
    {
        notifyClients(ws, "json");
    }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:
        client->text(gatherSystemData());
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;

    case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;

    case WS_EVT_DATA:
        // handleWebSocketMessage(arg, data, len);
        // Serial.printf("Received data from client #%u\n", client->id());
        break;

    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
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
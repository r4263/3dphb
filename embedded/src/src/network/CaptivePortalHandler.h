#ifndef CAPTIVE_PORTAL_HANDLER_H
#define CAPTIVE_PORTAL_HANDLER_H

#include <ESPAsyncWebServer.h>
#include <src/data/filetools.h>

class CaptivePortalHandler : public AsyncWebHandler
{
public:
    CaptivePortalHandler();          // Constructor
    virtual ~CaptivePortalHandler(); // Destructor

    bool canHandle(AsyncWebServerRequest *request) override;
    void handleRequest(AsyncWebServerRequest *request) override;

private:
    const char *index_html_path = "/index.html";
};

#endif // CAPTIVE_PORTAL_HANDLER_H

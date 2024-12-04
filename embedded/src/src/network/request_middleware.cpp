#include <src/network/request_middleware.h>

bool validateRequest(AsyncWebServerRequest *request, uint8_t *data, size_t len)
{
    String expectedToken = generateSHA256(request->client()->remoteIP().toString());

    StaticJsonDocument<256> jsonDoc;
    DeserializationError error = deserializeJson(jsonDoc, data, len);

    if (error)
    {
        Serial.printf("Erro ao parsear JSON: %s\n", error.c_str());
        return false;
    }

    if (!jsonDoc.containsKey("token") || jsonDoc["token"].as<String>() != expectedToken)
    {
        return false;
    }

    return true;
}
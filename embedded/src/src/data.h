#ifndef DATA_H
#define DATA_H

#include <Arduino.h>
#include <ArduinoJson.h>

typedef struct
{
    String SSID;
    String PASS;
    uint16_t MCASTPORT;
    uint16_t TCPPORT;
    IPAddress MCASTGROUP;
    String INTERNALSSID;
    String INTERNALPASS;

    bool setSSID(String SSID)
    {
        this->SSID = SSID;

        return this->SSID == SSID ? true : false;
    }

    bool setPASS(String PWK)
    {
        this->PASS = PWK;

        return this->PASS == PWK ? true : false;
    }

    bool setMCASTPORT(uint16_t PORT)
    {
        this->MCASTPORT = PORT;

        return this->MCASTPORT == PORT ? true : false;
    }

    bool setTCPPORT(uint16_t PORT)
    {
        this->TCPPORT = PORT;

        return this->TCPPORT == PORT ? true : false;
    }

    bool setINTERNALSSID(String ISSID)
    {
        this->INTERNALSSID = ISSID;

        return this->INTERNALSSID == ISSID ? true : false;
    }

    bool setINTERNALPASS(String IPASS)
    {
        this->INTERNALPASS = IPASS;

        return this->INTERNALPASS == IPASS ? true : false;
    }

    bool setMCASTGROUP(String GROUP)
    {
        if (this->MCASTGROUP.fromString(GROUP))
            return true;
        else
            return false;
    }

    void setArgs(JsonObject Args)
    {
        this->MCASTGROUP.fromString(Args["MCASTADDR"].as<String>());
        this->MCASTPORT = Args["MCASTPORT"].as<uint16_t>();
        this->TCPPORT = Args["TCPPORT"].as<uint16_t>();
        this->SSID = Args["SSID"].as<String>();
        this->PASS = Args["PWK"].as<String>();
        this->INTERNALSSID = Args["INTERNALSSID"].as<String>();
        this->INTERNALPASS = Args["INTERNALPWK"].as<String>();
    }

    String mountObject()
    {
        JsonDocument doc;
        String returningString;

        JsonObject network = doc["NETWORK"].to<JsonObject>();
        network["SSID"] = this->SSID;
        network["PWK"] = this->PASS;
        network["MCASTADDR"] = this->MCASTGROUP;
        network["MCASTPORT"] = this->MCASTPORT;
        network["TCPPORT"] = this->TCPPORT;
        network["INTERNALSSID"] = this->INTERNALSSID;
        network["INTERNALPWK"] = this->INTERNALPASS;

        serializeJson(doc, returningString);

        return returningString;
    }

} Connection;

/**
 * Struct used for registering error messages
 * obj.ERR -> `Receive the error message of the registered error.`
 * obj.STATUS -> `Error flag. use FALSE to inform there's an error.`
 */
typedef struct
{
    bool STATUS;
    String ERR;

    void CLEAR()
    {
        this->ERR = "";
        this->STATUS = true;
    }
} status;

#endif
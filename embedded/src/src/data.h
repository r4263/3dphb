#include <Arduino.h>
struct Connection
{
    String SSID;
    String PASS;
    IPAddress IPV4;
    IPAddress MULTICASTGROUP;
};

/**
 * Struct used for registering error messages
 * obj.ERR -> `Receive the error message of the registered error.`
 * obj.STATUS -> `Error flag. use FALSE to inform there's an error.`
 */
struct status
{
    bool STATUS;
    String ERR;

    void CLEAR()
    {
        this->ERR = "";
        this->STATUS = true;
    }
};
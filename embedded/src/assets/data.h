#include <Arduino.h>

typedef struct Connection
{
    String SSID;
    String PASS;
    IPAddress ipv4;
    IPAddress MULTICASTGROUP;
};

typedef struct status
{
};
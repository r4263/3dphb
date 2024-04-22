#include <Arduino.h>

typedef struct Connection
{
    char connectionType;
    char connectionMode;
    char SSID;
    char PASS;
} ConnectionConfig;
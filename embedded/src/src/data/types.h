#ifndef TYPES_H
#define TYPES_H

#include <WiFi.h>

// Beep length control enum
enum BeepLength
{
    DURATION_SHORT = 33,
    DURATION_NORMAL = 50,
    DURATION_MEDIUM = 75,
    DURATION_LONG = 100
};

enum BeepStates
{
    turn_on = 512,
    turn_off = 0
};

// Beep frequency control enum
enum BeepTone
{
    TONE_BASS = 440,
    TONE_MEDIUM = 690,
    TONE_HIGH = 1000
};

enum BeeperActions
{
    BEEP = 1,
    TEST = 0
};

enum WiFiMode
{
    IDLE,
    AP_MODE,
    STA_MODE
};

enum WiFiState
{
    OPERATIONAL,
    TRANSITIONING,
    OFF
};

/**
 * OFF = 0
 * ON = 1
 */
enum ONOFF
{
    off,
    on
};

enum ControlModes
{
    hysteresis,
    pid
};

#endif
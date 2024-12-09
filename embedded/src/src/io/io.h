#ifndef IO_H
#define IO_H

#define TFT_CHANNEL 0
#define HEATER_CHANNEL 1
#define BUZZER_CHANNEL 2

#include <Arduino.h>
#include <src/data/data.h>

extern void initializePinout(void);

#endif
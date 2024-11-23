#ifndef PERIPHERALPROCESSING_H
#define PERIPHERALPROCESSING_H

#include <src/definitions.h>
#include <PID_v1.h>

extern void peripheralProcessing(void *pvParameters);
extern TaskHandle_t pProcessingHandle;

// extern void refreshCPUTemperature(GlobalState *state);
// extern void refreshBedTemperature(GlobalState *state);
extern void calculatePID(void);

#endif
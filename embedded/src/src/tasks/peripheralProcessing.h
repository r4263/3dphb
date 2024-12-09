#ifndef PERIPHERALPROCESSING_H
#define PERIPHERALPROCESSING_H

#include <src/definitions.h>
#include <src/data/states/global.h>
#include <PID_v1.h>
#include <src/io/io.h>

#define PID_SAMPLE_TIME 100
#define ITERATION_DELAY 44

extern void peripheralProcessing(void *pvParameters);
extern TaskHandle_t pProcessingHandle;

extern void updatePIDTunnings(void);
extern double getBedTemperature(void);
extern void calculatePID(void);

#endif
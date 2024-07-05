#ifndef INIT_H
#define INIT_H

#include <Arduino.h>
#include <src/data.h>
#include <src/definitions.h>

extern void Init(void *pvParameters);
extern TaskHandle_t InitTask;

#endif
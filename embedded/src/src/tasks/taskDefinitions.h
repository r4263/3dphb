#ifndef TASKDEFINITIONS_H
#define TASKDEFINITIONS_H

#include <Arduino.h>
#include <src/tasks/beeper.h>
#include <src/tasks/networkScanner.h>
#include <src/tasks/peripheralProcessing.h>
#include <src/tasks/networkManager.h>
#include <src/tasks/hmiHandler.h>
#include <src/data/identifiers.h>

extern void initializeTasks(void);

#endif
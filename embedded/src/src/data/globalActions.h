#ifndef GLOBALACTIONS_H
#define GLOBALACTIONS_H

#include <Arduino.h>
#include <src/data/types.h>
#include <src/data/identifiers.h>

typedef struct
{
    void beep(BeeperActions beepType);
} GlobalActions;

#endif
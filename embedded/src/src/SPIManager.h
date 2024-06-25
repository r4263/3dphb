#ifndef SAMPLE_MANAGER_H
#define SAMPLE_MANAGER_H

#include <Arduino.h>

class SPImanager
{

public:
    bool revoke();
    bool getTurn();
    uint8_t getGPIOnumber(uint8_t gpio);
    bool;

private:
    SPImanager();
};

#endif
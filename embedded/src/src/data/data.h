#ifndef DATA_H
#define DATA_H

#include <src/data/identifiers.h>
#include <src/data/types.h>
#include <src/data/states/network.h>
#include <src/data/states/global.h>
#include <src/data/globalActions.h>

extern boolean initializeMutexes(void); // Function used to initialize all data access control mutexes, returns true if its everything ok

extern GlobalState APPLICATION_STATE;
extern NetworkState NETWORK_STATE;
extern GlobalActions DEVICE;

// Status struct for error handling
typedef struct
{
    bool STATUS;
    String ERR;
    void CLEAR(); // Keep this inline, as it's a very simple method
} status;

// typedef struct
// {
//     // To be defined later
// } Volatile;

// typedef struct
// {
//     // To be defined later
// } UIState;

#endif
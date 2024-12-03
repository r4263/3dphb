#include <src/init.h>

/**
 * Function used to concentrate all initialization processes, cleaning setup() function;
 * This could be better, like: implement initialization verification as a lot of the called functions inside has a boolean return
 */
void initApplicationVitals(void)
{
    // Initialize State vitals and control access mutexes
    initializeMutexes();

    // Initialize filesystem(before screen to avoid SPI conflict - which can be dangerous, but very unlikely to happen)
    initFS();

    initDatabase();

    initializePinout();

    initializeTasks(); // The actual infinite running tasks
}
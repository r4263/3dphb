#include <src/data/globalActions.h>

void GlobalActions::beep(BeeperActions beepType)
{
    xTaskNotify(beeperHandle, beepType, eSetValueWithOverwrite); // using Task notifications to execute the beep routine
}
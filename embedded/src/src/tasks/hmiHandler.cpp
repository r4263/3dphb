#include <src/tasks/hmiHandler.h>

void hmiHandler(void *pvParameters)
{

    // Initialize screen vital functions: touchscreen handler and lvgl's gutter libraries
    initializeScreen();

    while (true)
    {
        lv_task_handler();
        lv_tick_inc(5);
        usleep(5000);
    }
}
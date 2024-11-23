#ifndef MACROS_H
#define MACROS_H

#define SEMAPHORE_WRAPPER(mutex, body)        \
    if (xSemaphoreTake(mutex, portMAX_DELAY)) \
    {                                         \
        body;                                 \
        xSemaphoreGive(mutex);                \
    }

#endif
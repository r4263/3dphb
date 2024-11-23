#include <src/io/io.h>

void initializePinout(void)
{
    pinMode(TFT_BRIGHTNESS, OUTPUT);
    digitalWrite(TFT_BRIGHTNESS, HIGH);
}

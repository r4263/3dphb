#include <src/io/io.h>

void initializePinout(void)
{
    ledcSetup(TFT_CHANNEL, 10000, 10);
    ledcSetup(HEATER_CHANNEL, 10000, 10);
    ledcSetup(BUZZER_CHANNEL, (uint16_t)APPLICATION_STATE.getTone(), 8);

    ledcAttachPin(TFT_BRIGHTNESS, TFT_CHANNEL);
    ledcAttachPin(HEATER_PWM, HEATER_CHANNEL);
    ledcAttachPin(BUZZER, BUZZER_CHANNEL);

    ledcWrite(TFT_CHANNEL, map(APPLICATION_STATE.getBrightness(), 0, 100, 20, 1023));

    pinMode(PWR, OUTPUT);
    pinMode(NTC_PIN, INPUT);

    digitalWrite(PWR, LOW);
}

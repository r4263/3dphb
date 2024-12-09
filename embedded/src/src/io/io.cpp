#include <src/io/io.h>

void initializePinout(void)
{
    // PWR
    // HEATER_PWM
    // BUZZER
    // NTC_PIN
    // TFT_BRIGHTNESS

    ledcSetup(TFT_CHANNEL, 10000, 10);
    ledcSetup(HEATER_CHANNEL, 10000, 10);
    ledcSetup(BUZZER_CHANNEL, (uint16_t)APPLICATION_STATE.getTone(), 8);

    ledcAttachPin(TFT_BRIGHTNESS, TFT_CHANNEL);
    ledcAttachPin(HEATER_PWM, HEATER_CHANNEL);
    ledcAttachPin(BUZZER, BUZZER_CHANNEL);

    ledcWrite(TFT_CHANNEL, 512);
    ledcWrite(HEATER_CHANNEL, 512);
    ledcWrite(BUZZER_CHANNEL, 0);

    pinMode(PWR, OUTPUT);
    pinMode(NTC_PIN, INPUT);

    digitalWrite(PWR, LOW);
}

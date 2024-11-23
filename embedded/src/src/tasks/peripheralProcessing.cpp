#include <src/tasks/peripheralProcessing.h>

// PID pid(bed_temp, output_pwm, setpoint, kp, ki, kd, DIRECT);

void peripheralProcessing(void *pvParameters)
{
    // pid.SetMode(AUTOMATIC);
    // pid.SetOutputLimits(0, 1023);

    // pinMode(NTC_PIN, INPUT);
    // pinMode(PWR, OUTPUT);

    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(100));

        // if (xSemaphoreTake(globalStateMutex, portMAX_DELAY))
        // {
        //     refreshCPUTemperature(&STATE);
        //     refreshBedTemperature(&STATE);
        //     xSemaphoreGive(globalStateMutex);
        // }

        // if (STATE.output_enable)
        // {
        //     calculatePID();

        //     if (!digitalRead(PWR))
        //     {
        //         digitalWrite(PWR, HIGH);
        //         vTaskDelay(pdMS_TO_TICKS(1000));
        //         ledcWrite(1, STATE.output_pwm);
        //     }
        // }
        // else
        // {
        //     ledcWrite(1, 0);

        //     if (xSemaphoreTake(globalStateMutex, portMAX_DELAY))
        //     {
        //         STATE.output_pwm = 0;
        //         xSemaphoreGive(globalStateMutex);
        //     }

        //     if (digitalRead(PWR))
        //         digitalWrite(PWR, LOW);
        // }

        // Serial.println(STATE.output_pwm);
    }
}

void refreshCPUTemperature(GlobalState *state)
{
    // state->setCPUTemperature(temperatureRead());
}

void refreshBedTemperature(GlobalState *state)
{
    double Vs = 3.3;
    double To = 298.15;
    double Ro = 10000;

    double Vout, Rt = 0;
    double T, Tc, adc = 0;

    adc = analogRead(NTC_PIN);

    Vout = adc * Vs / ADC_RES;
    Rt = RESISTOR * Vout / (Vs - Vout);
    T = 1 / (1 / To + log(Rt / Ro) / BETA);
    Tc = T - 273.15;

    // state->setBedTemperature(Tc);
}

void calculatePID(void)
{
    // pid.Compute();
}
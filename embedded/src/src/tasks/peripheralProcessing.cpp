#include <src/tasks/peripheralProcessing.h>

double Setpoint, Input, Output, lastOutput, kp, ki, kd;
ControlModes currentMode;
bool lastOutputState, outputState;

PID tControl(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);

void peripheralProcessing(void *pvParameters)
{
    tControl.SetMode(APPLICATION_STATE.getControlMode() == ControlModes::pid ? AUTOMATIC : MANUAL);
    tControl.SetOutputLimits(0, 1023);       // 10 bits output resolution
    tControl.SetSampleTime(PID_SAMPLE_TIME); // sample time
    updatePIDTunnings();

    while (true)
    {
        currentMode = APPLICATION_STATE.getControlMode();
        outputState = APPLICATION_STATE.getOutputState();

        Input = getBedTemperature();
        APPLICATION_STATE.setBedTemperature(Input);

        APPLICATION_STATE.setCPUTemperature((double)temperatureRead());

        // Handle pid keys changes
        if (APPLICATION_STATE.hasPIDTunningChanged())
            updatePIDTunnings();

        // Handle setpoint changes
        if (APPLICATION_STATE.hasPIDSetpointChanged())
            Setpoint = APPLICATION_STATE.getSetpoint();

        // Handle control mode changes
        if (APPLICATION_STATE.hasControlmodeChanged())
            tControl.SetMode(currentMode == ControlModes::pid ? AUTOMATIC : MANUAL);

        if (outputState) // if the output is enabled
        {
            switch (currentMode)
            {
            case ControlModes::pid:
                if (tControl.Compute())
                {
                    digitalWrite(PWR, HIGH);

                    if (lastOutputState != outputState) // if the state changed, delay the pwm ramping up by 1 second
                        vTaskDelay(pdMS_TO_TICKS(1000));

                    ledcWrite(HEATER_CHANNEL, (uint32_t)Output);
                }
                break;

            case ControlModes::hysteresis:
                if (Input > Setpoint + APPLICATION_STATE.getUpperHysteresisValue())
                    ledcWrite(HEATER_CHANNEL, 0);
                if (Input < Setpoint - APPLICATION_STATE.getLowerHysteresisValue())
                    ledcWrite(HEATER_CHANNEL, 1023);
                break;
            }
        }
        else
        {
            ledcWrite(HEATER_CHANNEL, 0);
            APPLICATION_STATE.setPWM(0);

            vTaskDelay(pdMS_TO_TICKS(200));

            if (digitalRead(PWR))
                digitalWrite(PWR, LOW);
        }

        if (lastOutputState != outputState)
            lastOutputState = outputState;

        // handle feeding the application state the output changes
        if (Output != lastOutput)
        {
            APPLICATION_STATE.setPWM(Output);
            lastOutput = Output;
        }

        vTaskDelay(pdMS_TO_TICKS(ITERATION_DELAY));
    }
}

void updatePIDTunnings(void)
{
    kp = APPLICATION_STATE.getKp();
    ki = APPLICATION_STATE.getKi();
    kd = APPLICATION_STATE.getKd();

    tControl.SetTunings(kp, ki, kd);
}

double getBedTemperature(void)
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

    return Tc;
}
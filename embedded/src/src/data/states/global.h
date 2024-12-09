#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H

#include <Arduino.h>
#include <src/data/macros.h>
#include <src/data/types.h>
#include <src/data/identifiers.h>
#include <LittleFS.h>

// GlobalState struct to handle device state
typedef struct GlobalState
{
    // Setting local vars and a initial state/value to them
    double cpu_temp = 0;
    double bed_temp = 0;
    double output_pwm = 0;
    double setpoint = 30;
    double kp = 0;
    double ki = 0;
    double kd = 0;
    uint8_t lh = 0;
    uint8_t hh = 0;
    ControlModes control_mode;
    boolean updatedPIDTunnings = false;
    boolean updatedPIDSetpoint = false;
    boolean updatedControlMode = false;
    boolean output_enable = false;
    boolean beep_enable = true;
    BeepLength beep_length = DURATION_NORMAL;
    BeepTone beep_frequency = TONE_MEDIUM;
    fs::LittleFSFS filesystem;
    // boolean fsState = false;

    // Getters and setters
    // Output PWM
    void setPWM(uint16_t pwm);
    uint16_t getPWM(void);

    // Beep Tone
    void setTone(BeepTone tone);
    BeepTone getTone(void);

    // Beep duration
    void setDuration(BeepLength length);
    BeepLength getDuration(void);

    // PID temperature setpoint
    void setSetpoint(double setpoint);
    double getSetpoint(void);

    // PID variables
    void setKp(double kp);
    void setKi(double ki);
    void setKd(double kd);
    double getKp(void);
    double getKi(void);
    double getKd(void);
    boolean hasPIDTunningChanged(void);
    boolean hasPIDSetpointChanged(void);

    ControlModes getControlMode(void);
    void setControlMode(ControlModes mode);
    boolean hasControlmodeChanged(void);

    // Upper hysteresis
    void setUpperHysteresisValue(uint8_t hh);
    uint8_t getUpperHysteresisValue(void);

    // Lower hysteresis
    void setLowerHysteresisValue(uint8_t lh);
    uint8_t getLowerHysteresisValue(void);

    // PWM output enable flag
    void enableOutput();
    void disableOutput();
    void setOutputState(boolean state);
    boolean getOutputState(void);

    // Heated bed temperature
    void setBedTemperature(double temp);
    double getBedTemperature(void);

    // CPU temperature
    void setCPUTemperature(double temp);
    double getCPUTemperature(void);

    // Beeper exclusive flags
    void enableBeeper();
    void disableBeeper();
    void setBeeperState(boolean state);
    boolean getBeeperState();
} GlobalState;

#endif
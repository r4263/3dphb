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
    boolean updatedPIDTunnings = false;
    boolean updatedPIDSetpoint = false;
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

    // void setFSState(boolean state);
    // boolean isFsInitialized(void);

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

// Connection struct
// typedef struct
// {
//     String SSID;
//     String PASS;
//     uint16_t MCASTPORT;
//     uint16_t TCPPORT;
//     IPAddress MCASTGROUP;
//     String INTERNALSSID;
//     String INTERNALPASS;
//     uint32_t SCANINTERVAL;

//     bool setSSID(String SSID);
//     bool setPASS(String PWK);
//     bool setMCASTPORT(uint16_t PORT);
//     bool setTCPPORT(uint16_t PORT);
//     bool setINTERNALSSID(String ISSID);
//     bool setINTERNALPASS(String IPASS);
//     bool setMCASTGROUP(String GROUP);
//     bool setSCANINTERVAL(uint32_t INTERVAL);
//     void setArgs(JsonObject Args);
//     String mountObject();
// } Connection;
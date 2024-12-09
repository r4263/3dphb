#include <src/data/states/global.h>

// Getters and setters

ControlModes GlobalState::getControlMode(void)
{
    ControlModes mode;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        mode = this->control_mode;
    });

    return mode;
}

void GlobalState::setControlMode(ControlModes mode)
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->control_mode = mode;
        this->updatedControlMode = true;
    });
}

boolean GlobalState::hasControlmodeChanged(void)
{
    bool isUpdated;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        isUpdated = this->updatedControlMode;

        if (isUpdated)
            this->updatedControlMode = false;
    });

    return isUpdated;
}

// Output PWM
void GlobalState::setPWM(uint16_t pwm)
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->output_pwm = this->output_enable ? pwm : 0;
    });
}

uint16_t GlobalState::getPWM(void)
{
    uint16_t outPwm;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        outPwm = this->output_pwm;
    });

    return outPwm;
};

// FileSystem
// fs::LittleFSFS GlobalState::FILESYSTEM(void)
// {
//     // fs::LittleFSFS fs;

//     // SEMAPHORE_WRAPPER(globalStateMutex, {
//     //     fs = this->filesystem;
//     // });

//     // return fs;

//     return this->filesystem;
// }

// Beep Tone
void GlobalState::setTone(BeepTone tone)
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->beep_frequency = tone;
    });
}

BeepTone GlobalState::getTone(void)
{
    BeepTone tone;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        tone = this->beep_frequency;
    });

    return tone;
};

// Beep duration
void GlobalState::setDuration(BeepLength length)
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->beep_length = length;
    });
}

BeepLength GlobalState::getDuration(void)
{
    BeepLength duration;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        duration = this->beep_length;
    });

    return duration;
};

// PID temperature setpoint
void GlobalState::setSetpoint(double setpoint)
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->setpoint = setpoint;
        this->updatedPIDSetpoint = true;
    });
};

double GlobalState::getSetpoint(void)
{
    double sp;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        sp = this->setpoint;
    });

    return sp;
};

// PID variables
void GlobalState::setKp(double kp)
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        if (this->kp != kp)
        {
            this->updatedPIDTunnings = true;
            this->kp = kp;
        }
    });
};

void GlobalState::setKi(double ki)
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        if (this->ki != ki)
        {
            this->updatedPIDTunnings = true;
            this->ki = ki;
        }
    });
};

void GlobalState::setKd(double kd)
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        if (this->kd != kd)
        {
            this->updatedPIDTunnings = true;
            this->kd = kd;
        }
    });
};

double GlobalState::getKp(void)
{
    double kp;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        kp = this->kp;
    });

    return kp;
};

double GlobalState::getKi(void)
{
    double ki;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        ki = this->ki;
    });

    return ki;
};

double GlobalState::getKd(void)
{
    double kd;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        kd = this->kd;
    });

    return kd;
};

boolean GlobalState::hasPIDTunningChanged(void) // Update listener, when read it toggles itself to false to prevent multiple mutex accesses and redundant iterations
{
    boolean isUpdated;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        isUpdated = this->updatedPIDTunnings;

        if (isUpdated)
            this->updatedPIDTunnings = false;
    });

    return isUpdated;
};

boolean GlobalState::hasPIDSetpointChanged(void) // Update listener, when read it toggles itself to false to prevent multiple mutex accesses and redundant iterations
{
    boolean isUpdated;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        isUpdated = this->updatedPIDSetpoint;

        if (isUpdated)
            this->updatedPIDSetpoint = false;
    });

    return isUpdated;
};

// Upper hysteresis
void GlobalState::setUpperHysteresisValue(uint8_t hh)
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->hh = hh;
    });
}

uint8_t GlobalState::getUpperHysteresisValue(void)
{
    uint8_t hh;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        hh = this->hh;
    });

    return hh;
}

// Lower hysteresis
void GlobalState::setLowerHysteresisValue(uint8_t lh)
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->lh = lh;
    });
}

uint8_t GlobalState::getLowerHysteresisValue(void)
{
    uint8_t lh;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        lh = this->lh;
    });

    return lh;
}

// PWM output enable flag
void GlobalState::enableOutput()
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->output_enable = true;
    });
};

void GlobalState::disableOutput()
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->output_enable = false;
    });
};

void GlobalState::setOutputState(boolean state)
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->output_enable = state;
    });
};

boolean GlobalState::getOutputState(void)
{
    boolean state;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        state = this->output_enable;
    });

    return state;
};

// Heated bed temperature
void GlobalState::setBedTemperature(double temp)
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->bed_temp = temp;
    });
};

double GlobalState::getBedTemperature(void)
{
    double temp;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        temp = this->bed_temp;
    });

    return temp;
};

// CPU temperature
void GlobalState::setCPUTemperature(double temp)
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->cpu_temp = temp;
    });
};

double GlobalState::getCPUTemperature(void)
{
    double temp;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        temp = this->cpu_temp;
    });

    return temp;
};

// Beeper exclusive flags
void GlobalState::enableBeeper()
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->output_enable = true;
    });
};

void GlobalState::disableBeeper()
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->output_enable = false;
    });
};

void GlobalState::setBeeperState(boolean state)
{
    SEMAPHORE_WRAPPER(globalStateMutex, {
        this->output_enable = state;
    });
};

boolean GlobalState::getBeeperState()
{
    boolean state;
    SEMAPHORE_WRAPPER(globalStateMutex, {
        state = this->beep_enable;
    });

    return state;
};

// bool Connection::setSSID(String SSID)
// {
//     this->SSID = SSID;
//     return this->SSID == SSID;
// }

// bool Connection::setPASS(String PWK)
// {
//     this->PASS = PWK;
//     return this->PASS == PWK;
// }

// bool Connection::setMCASTPORT(uint16_t PORT)
// {
//     this->MCASTPORT = PORT;
//     return this->MCASTPORT == PORT;
// }

// bool Connection::setTCPPORT(uint16_t PORT)
// {
//     this->TCPPORT = PORT;
//     return this->TCPPORT == PORT;
// }

// bool Connection::setINTERNALSSID(String ISSID)
// {
//     this->INTERNALSSID = ISSID;
//     return this->INTERNALSSID == ISSID;
// }

// bool Connection::setINTERNALPASS(String IPASS)
// {
//     this->INTERNALPASS = IPASS;
//     return this->INTERNALPASS == IPASS;
// }

// bool Connection::setMCASTGROUP(String GROUP)
// {
//     return this->MCASTGROUP.fromString(GROUP);
// }

// bool Connection::setSCANINTERVAL(uint32_t INTERVAL)
// {
//     this->SCANINTERVAL = INTERVAL;
//     return this->SCANINTERVAL == INTERVAL;
// }

// void Connection::setArgs(JsonObject Args)
// {
//     this->MCASTGROUP.fromString(Args["MCASTADDR"].as<String>());
//     this->MCASTPORT = Args["MCASTPORT"].as<uint16_t>();
//     this->TCPPORT = Args["TCPPORT"].as<uint16_t>();
//     this->SSID = Args["SSID"].as<String>();
//     this->PASS = Args["PWK"].as<String>();
//     this->SCANINTERVAL = Args["SCANINTERVAL"].as<uint32_t>();
// }

// String Connection::mountObject()
// {
//     JsonDocument doc;
//     String returningString;

//     JsonObject network = doc.createNestedObject("NETWORK");
//     network["SSID"] = this->SSID;
//     network["PWK"] = this->PASS;
//     network["MCASTADDR"] = this->MCASTGROUP.toString();
//     network["MCASTPORT"] = this->MCASTPORT;
//     network["TCPPORT"] = this->TCPPORT;
//     network["SCANINTERVAL"] = this->SCANINTERVAL;

//     serializeJson(doc, returningString);
//     return returningString;
// }

// void status::CLEAR()
// {
//     this->ERR = "";
//     this->STATUS = true;
// }
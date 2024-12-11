#include <src/init.h>

/**
 * Function used to concentrate all initialization processes, cleaning setup() function;
 * This could be better, like: implement initialization verification as a lot of the called functions inside has a boolean return
 */
void initApplicationVitals(void)
{
    // Initialize State vitals and control access mutexes
    initializeMutexes();

    // Initialize filesystem(before screen to avoid SPI conflict - which can be dangerous, but very unlikely to happen)
    initFS();

    // Initialize database - create and supply default data if not present
    initDatabase();

    // Process the stored data and supply it to the application state
    JsonDocument storedData;
    DeserializationError error = deserializeJson(storedData, queryDatabase(selectAllConfigsQuery, true));

    APPLICATION_STATE.setDuration(storedData[0]["beep_duration"].as<BeepLength>());
    APPLICATION_STATE.setTone(storedData[0]["beep_tone"].as<BeepTone>());
    APPLICATION_STATE.setKp(storedData[0]["kp"].as<double>());
    APPLICATION_STATE.setKi(storedData[0]["ki"].as<double>());
    APPLICATION_STATE.setKd(storedData[0]["kd"].as<double>());
    APPLICATION_STATE.setUpperHysteresisValue(storedData[0]["hh"].as<uint8_t>());
    APPLICATION_STATE.setLowerHysteresisValue(storedData[0]["lh"].as<uint8_t>());
    APPLICATION_STATE.setSetpoint(storedData[0]["setpoint"].as<double>());
    APPLICATION_STATE.setControlMode(storedData[0]["control_mode"].as<ControlModes>());
    APPLICATION_STATE.setBrightness(storedData[0]["brightness"].as<uint8_t>());

    Serial.println(storedData[0]["brightness"].as<uint8_t>());
    Serial.println(APPLICATION_STATE.getBrightness());

    // Freeing the used memory
    storedData.clear();

    initializePinout();

    initializeTasks(); // The actual infinite running tasks
}
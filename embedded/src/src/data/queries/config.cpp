#include <src/data/queries/config.h>

const char *createConfigTableQuery = R"(
    CREATE TABLE configs (
    kp FLOAT,
    ki FLOAT,
    kd FLOAT,
    hh INTEGER,
    lh INTEGER,
    brightness INTEGER,
    setpoint INTEGER,
    control_mode INTEGER,
    beep_tone INTEGER,
    beep_duration INTEGER,
    wifi_state INTEGER,
    wifi_mode INTEGER,
    wifi_scan_interval INTEGER,
    network_ssid TEXT,
    network_password TEXT,
    multicast_group TEXT,
    multicast_port INTEGER
  );
  )";

const char *insertDefaultData = R"(
  INSERT INTO configs (kp, ki, kd, hh, lh, brightness, setpoint, control_mode, beep_tone, beep_duration, wifi_state, wifi_mode, wifi_scan_interval, network_ssid, network_password, multicast_group, multicast_port) VALUES (1.0, 1.0, 1.0, 3, 3, 50, 30, 1, 440, 50, 0, 0, 60, '', '', '', 0);
)";

const char *selectAllConfigsQuery = R"(
    SELECT * FROM configs
)";
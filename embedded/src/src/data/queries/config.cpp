#include <src/data/queries/config.h>

const char *createConfigTableQuery = R"(
    CREATE TABLE configs (
    kp FLOAT,
    ki FLOAT,
    kd FLOAT,
    setpoint INTEGER,
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
  INSERT INTO configs (
    kp, ki, kd, setpoint, beep_tone, beep_duration, wifi_state, wifi_mode, wifi_scan_interval,
    network_ssid, network_password, multicast_group, multicast_port
  ) VALUES (0.0, 0.0, 0.0, 0, 440, 50, 0, 0, 60, '', '', '', 0);
)";

const char *selectAllConfigsQuery = R"(
    SELECT * FROM configs
)";

const char *updateRowConfigQuery = R"()";

// extern const char *insertDataQuery
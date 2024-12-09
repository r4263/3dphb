interface DeviceState {
    kp: number,
    ki: number,
    kd: number,
    setpoint: number,
    bed_temp: number,
    cpu_temp: number,
    heater_enabled: boolean,
    control_mode: number,
    lh: number,
    hh: number
}

type Notification = {
    id: string;
    message: string;
};

type NotificationContextType = {
    pushNotification: (message: string) => void;
};

type TabsOptions = "state" | "control";

type ControlModes = "pid" | "hysteresis";

export { DeviceState, Notification, NotificationContextType, TabsOptions, ControlModes }

// { "kp": 1, "ki": 1, "kd": 1, "setpoint": 40, "bed_temp": 14.78511318, "cpu_temp": 46.6, "heater_enabled": true, "control_mode": 1, "lh": 3, "hh": 3 }
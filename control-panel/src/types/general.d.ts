interface DeviceState {
    kp?: number,
    ki?: number,
    kd?: number,
    setpoint?: number,
    bed_temp?: number,
    cpu_temp?: number,
    heater_enabled?: boolean,
    control_mode?: number,
    lh?: number,
    hh?: number
}

type TabsOptions = "state" | "control";

type ControlModes = "pid" | "hysteresis";

type NotificationLevel = "success" | "error" | "warning" | "info";

interface Notification {
    id: string;
    message: string;
    level: NotificationLevel;
}

interface NotificationContextType {
    pushNotification: (options: { message: string; level?: NotificationLevel }) => void;
}

export { DeviceState, Notification, NotificationContextType, TabsOptions, ControlModes, NotificationLevel }

// { "kp": 1, "ki": 1, "kd": 1, "setpoint": 40, "bed_temp": 14.78511318, "cpu_temp": 46.6, "heater_enabled": true, "control_mode": 1, "lh": 3, "hh": 3 }
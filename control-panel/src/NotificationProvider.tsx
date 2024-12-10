import React, { createContext, useContext, useState, useCallback } from "react";
import { NotificationContextType, Notification, NotificationLevel } from "./types/general";

const NotificationContext = createContext<NotificationContextType | undefined>(undefined);

export const NotificationProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
    const [notifications, setNotifications] = useState<Notification[]>([]);

    const pushNotification = useCallback(({ message, level = "info" }: { message: string; level?: NotificationLevel }) => {
        const id = `${Date.now()}-${Math.random()}`;
        setNotifications((prev) => [...prev, { id, message, level }]);

        setTimeout(() => {
            setNotifications((prev) => prev.filter((notif) => notif.id !== id));
        }, 5000);
    }, []);

    const getNotificationStyle = (level: NotificationLevel) => {
        switch (level) {
            case "success":
                return "bg-green-500 text-white";
            case "error":
                return "bg-red-500 text-white";
            case "warning":
                return "bg-yellow-500 text-black";
            case "info":
            default:
                return "bg-blue-500 text-white";
        }
    };

    return (
        <NotificationContext.Provider value={{ pushNotification }}>
            {children}
            <div className="fixed bottom-4 right-4 space-y-2">
                {notifications.map((notif) => (
                    <div
                        key={notif.id}
                        className={`px-4 py-2 rounded shadow-lg transition-opacity ${getNotificationStyle(notif.level)}`}
                    >
                        <strong className="block capitalize">{notif.level}</strong>
                        <span>{notif.message}</span>
                    </div>
                ))}
            </div>
        </NotificationContext.Provider>
    );
};

export const useNotification = (): NotificationContextType => {
    const context = useContext(NotificationContext);
    if (!context) {
        throw new Error("useNotification must be used within a NotificationProvider");
    }
    return context;
};

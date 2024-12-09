import React, { createContext, useContext, useState, useCallback } from "react";
import { NotificationContextType, Notification } from "./types/general";


const NotificationContext = createContext<NotificationContextType | undefined>(undefined);

export const NotificationProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
    const [notifications, setNotifications] = useState<Notification[]>([]);

    const pushNotification = useCallback((message: string) => {
        const id = `${Date.now()}-${Math.random()}`;
        setNotifications((prev) => [...prev, { id, message }]);

        setTimeout(() => {
            setNotifications((prev) => prev.filter((notif) => notif.id !== id));
        }, 5000);
    }, []);

    return (
        <NotificationContext.Provider value={{ pushNotification }}>
            {children}
            <div className="fixed bottom-4 right-4 space-y-2">
                {notifications.map((notif) => (
                    <div
                        key={notif.id}
                        className="bg-black text-white px-4 py-2 rounded shadow-lg transition-opacity"
                    >
                        {notif.message}
                    </div>
                ))}
            </div>
        </NotificationContext.Provider>
    );
};

export const useNotification = (): NotificationContextType => {
    const context = useContext(NotificationContext);
    if (!context) {
        throw new Error();
    }
    return context;
};

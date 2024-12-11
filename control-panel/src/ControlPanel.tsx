import { useCallback, useEffect, useState } from "react";
import * as Tabs from "@radix-ui/react-tabs";
import * as Slider from "@radix-ui/react-slider";
import { Button } from "./components/ui/button";
import { Input } from "./components/ui/input";
import { Label } from "@radix-ui/react-label";
import * as ToggleGroup from "@radix-ui/react-toggle-group";
import { ControlModes, DeviceState, TabsOptions } from "./types/general";
import { useNotification } from "./NotificationProvider";
import { handleRequest } from "./requests";
import { messages } from "./constants";
import async from 'async';

export default function ControlPanel() {
    const { pushNotification } = useNotification();
    const [activeTab, setActiveTab] = useState<TabsOptions>("state");
    const [controlTabs, setControlTabs] = useState<ControlModes>("pid");

    const [heaterTemperature, setHeaterTemperature] = useState<number>(0);
    const [cpuTemperature, setCPUTemperature] = useState<number>(0);
    const [setpoint, setSetpoint] = useState<number>(30);
    const [heatingEnabled, setHeatingEnabled] = useState<boolean>(false);
    const [kp, setKp] = useState<number>(0);
    const [ki, setKi] = useState<number>(0);
    const [kd, setKd] = useState<number>(0);
    const [controlMode, setControlMode] = useState<number>(0);
    const [lh, setLH] = useState<number>(0);
    const [hh, setHH] = useState<number>(0);

    const [kpBackup, setKpBackup] = useState<number>(kp);
    const [kiBackup, setKiBackup] = useState<number>(kp);
    const [kdBackup, setKdBackup] = useState<number>(kp);

    const [lHysteresisBackup, setLHysteresisBackup] = useState<number>(lh);
    const [hHysteresisBackup, setHHysteresisBackup] = useState<number>(lh);

    useEffect(() => {
        const websocketUrl = `ws://${window.location.hostname}/ws`;
        // const websocketUrl = `ws://4.4.4.1/ws`;
        const socket = new WebSocket(websocketUrl);

        socket.onopen = () => {
            pushNotification({ message: "Conexão websocket estabelecida!", level: "success" });
        };

        socket.onmessage = (event) => {
            handleComponentRefresh(JSON.parse(event.data) as DeviceState);
        };

        socket.onclose = () => {
            pushNotification({ message: "Websocket desconectado!", level: "warning" });
        };

        socket.onerror = (error) => {
            // pushNotification({ message: "Erro no websocket!", level: "error" });
            console.log(error);
        };

        return () => {
            socket.close();
        };
    }, [pushNotification]);

    const handleComponentRefresh = (data: DeviceState) => {
        console.log(data);
        if (data.cpu_temp !== undefined) setCPUTemperature(data.cpu_temp);
        if (data.bed_temp !== undefined) setHeaterTemperature(data.bed_temp);
        if (data.heater_enabled !== undefined) setHeatingEnabled(data.heater_enabled);
        if (data.control_mode !== undefined) setControlMode(data.control_mode);
        if (data.setpoint !== undefined) setSetpoint(data.setpoint);

        if (data.kp !== undefined) {
            setKp(data.kp);
            setKpBackup(data.kp);
        }

        if (data.ki !== undefined) {
            setKi(data.ki);
            setKiBackup(data.ki)
        }

        if (data.kd !== undefined) {
            setKd(data.kd);
            setKdBackup(data.kd)
        }

        if (data.hh !== undefined) {
            setHH(data.hh);
            setHHysteresisBackup(data.hh);
        }

        if (data.lh !== undefined) {
            setLH(data.lh);
            setLHysteresisBackup(data.lh);
        }
    };

    const onError = useCallback(() => {
        pushNotification({ message: "Ocorreu um erro na requisição!", level: "error" });
    }, [pushNotification]);

    const handleToggleHeatingElement = useCallback((newMode: boolean) => {
        handleRequest("/state/set/heater", { heater_enable: newMode }).then(res => {
            if (res) pushNotification({ message: newMode ? messages.turnedHeaterOn : messages.turnedHeaterOff, level: "success" });
            else onError();
        }
        )
            .catch(onError);
    }, [onError, pushNotification]);

    const handleControlModeChanges = useCallback((mode: number) => {
        handleRequest("/state/set/control", { mode: mode }).then(res => {
            if (res) pushNotification({ message: mode === 0 ? messages.hysteresisSelected : messages.pidSelected, level: "success" });
            else onError();
        }
        )
            .catch(onError);
    }, [onError, pushNotification]);

    const handleSetpointChanges = useCallback((setpoint: number) => {
        handleRequest("/state/set/setpoint", { setpoint: setpoint }).then(res => {
            if (res) pushNotification({ message: `${messages.setpointAdjustedTo} ${setpoint}ºC`, level: "success" });
            else onError();
        }
        )
            .catch(onError);
    }, [onError, pushNotification]);

    const handlePIDChanges = useCallback((volatile: boolean = false) => {
        const requestQueue: Array<() => Promise<any>> = [];

        const sendRequest = (param: string, valor: number) => {
            return handleRequest(`/state/set/${param}`, { [param]: valor, volatile: volatile })
                .then((res) => {
                    if (res) {
                        pushNotification({
                            message: `${param} ajustado para ${valor}`,
                            level: "success",
                        });
                    } else {
                        onError();
                    }
                })
                .catch(onError);
        };

        if (kp !== kpBackup) requestQueue.push(() => sendRequest("kp", parseFloat(`${kp}`)));
        if (ki !== kiBackup) requestQueue.push(() => sendRequest("ki", parseFloat(`${ki}`)));
        if (kd !== kdBackup) requestQueue.push(() => sendRequest("kd", parseFloat(`${kd}`)));

        if (requestQueue.length > 0) {
            async.series(
                requestQueue.map((requestFn) => (callback: (err: any, result: any) => void) => {
                    requestFn()
                        .then(() => callback(null, true))
                        .catch((err) => callback(err, null));
                }),
                (err, results) => {
                    if (err) {
                        pushNotification({ message: `Erro na execução das requisições: ${err}`, level: "error" });
                    } else {
                        pushNotification({ message: "Todas as requisições foram processadas com sucesso!", level: "success" });
                    }
                }
            );
        } else {
            pushNotification({ message: "Nenhuma modificação nos valores!", level: "info" });
        }
    }, [onError, pushNotification, kp, ki, kd, kpBackup, kiBackup, kdBackup]);

    const handleHysteresisChanges = useCallback(() => {
        const requestQueue: Array<() => Promise<any>> = [];

        const sendRequest = (param: string, valor: number) => {
            return handleRequest(`/state/set/${param}`, { [param]: valor })
                .then((res) => {
                    if (res) {
                        pushNotification({
                            message: `${param} ajustado para ${valor}`,
                            level: "success",
                        });
                    } else {
                        onError();
                    }
                })
                .catch(onError);
        };

        if (hh !== hHysteresisBackup) requestQueue.push(() => sendRequest("hh", parseFloat(`${hh}`)));
        if (lh !== lHysteresisBackup) requestQueue.push(() => sendRequest("lh", parseFloat(`${lh}`)));

        if (requestQueue.length > 0) {
            async.series(
                requestQueue.map((requestFn) => (callback: (err: any, result: any) => void) => {
                    requestFn()
                        .then(() => callback(null, true))
                        .catch((err) => callback(err, null));
                }),
                (err, results) => {
                    if (err) {
                        pushNotification({ message: `Erro na execução das requisições: ${err}`, level: "error" });
                    } else {
                        pushNotification({ message: "Todas as requisições foram processadas com sucesso!", level: "success" });
                    }
                }
            );
        } else {
            pushNotification({ message: "Nenhuma modificação nos valores!", level: "info" });
        }
    }, [onError, pushNotification, hh, lh, hHysteresisBackup, lHysteresisBackup]);


    return (
        <div className="flex items-center justify-center min-h-screen bg-blue-100">
            <div className="w-full max-w-md p-6 bg-white rounded-lg shadow-lg">
                <Tabs.Root value={activeTab} onValueChange={(e) => setActiveTab(e as TabsOptions)}>
                    <Tabs.List className="flex mb-4 border-b">
                        <Tabs.Trigger
                            value="state"
                            className={`px-4 py-2 ${activeTab === "state" ? "border-b-2 border-blue-500" : ""}`}
                        >
                            Estado
                        </Tabs.Trigger>
                        <Tabs.Trigger
                            value="control"
                            className={`px-4 py-2 ${activeTab === "control" ? "border-b-2 border-blue-500" : ""}`}
                        >
                            Controle
                        </Tabs.Trigger>
                    </Tabs.List>

                    <Tabs.Content value="state" className="space-y-4">
                        <div>
                            <Label>Temperatura da CPU: {cpuTemperature}ºC</Label>
                            <div className="w-full bg-gray-200 rounded-full h-2.5">
                                <div
                                    className="bg-green-600 h-2.5 rounded-full"
                                    style={{ width: `${((cpuTemperature + 25) / 130) * 100}%` }}
                                ></div>
                            </div>
                        </div>
                        <div>
                            <Label>Temperatura do elemento: {heaterTemperature.toFixed(1)}ºC</Label>
                            <div className="w-full bg-gray-200 rounded-full h-2.5">
                                <div
                                    className="bg-blue-600 h-2.5 rounded-full"
                                    style={{
                                        width: `${((heaterTemperature + 25) / 175) * 100}%`,
                                    }}
                                ></div>
                            </div>
                        </div>
                        <div>
                            <Label>Modo de controle</Label>
                            <div className="flex items-center justify-center space-x-4 my-4">
                                <ToggleGroup.Root
                                    type="single"
                                    value={controlMode === 1 ? "pid" : "hysteresis"}
                                    className="flex space-x-2"
                                >
                                    <ToggleGroup.Item
                                        value="pid"
                                        onClick={() => handleControlModeChanges(1)}
                                        className={`px-4 py-2 border rounded-md ${controlMode === 1 ? "bg-black text-white" : "bg-gray-200 text-black"}`}
                                    >
                                        PID
                                    </ToggleGroup.Item>
                                    <ToggleGroup.Item
                                        value="hysteresis"
                                        onClick={() => handleControlModeChanges(0)}
                                        className={`px-4 py-2 border rounded-md ${controlMode === 0 ? "bg-black text-white" : "bg-gray-200 text-black"}`}
                                    >
                                        Histerese
                                    </ToggleGroup.Item>
                                </ToggleGroup.Root>
                            </div>
                        </div>
                        <div>
                            <Label>Alvo de temperatura: {setpoint}ºC</Label>
                            <Slider.Root
                                className="relative flex items-center select-none touch-none w-full h-5"
                                value={[setpoint]}
                                onValueChange={(newValue) => setSetpoint(newValue[0])}
                                onValueCommit={() => handleSetpointChanges(setpoint)}
                                min={30}
                                max={135}
                                step={1}
                                disabled={heatingEnabled}
                            >
                                <Slider.Track className="bg-gray-200 relative grow rounded-full h-2">
                                    <Slider.Range className="absolute bg-blue-500 rounded-full h-full" />
                                </Slider.Track>
                                <Slider.Thumb
                                    className="block w-5 h-5 bg-white shadow-lg rounded-full hover:bg-gray-50 focus:outline-none focus:ring-2 focus:ring-blue-500"
                                    aria-label="Arc value"
                                />
                            </Slider.Root>
                        </div>
                        <div className="flex items-center space-x-2">
                            <Button onClick={() => handleToggleHeatingElement(!heatingEnabled)} className="w-full bg-black text-white hover:bg-gray-800">
                                {heatingEnabled ? `Desabilitar aquecimento` : `Habilitar aquecimento`}
                            </Button>
                        </div>
                    </Tabs.Content>

                    <Tabs.Content value="control" className="space-y-4">
                        <Tabs.Root value={controlTabs} onValueChange={(e) => setControlTabs(e as ControlModes)}>

                            <Tabs.List className="flex mb-4 border-b">
                                <Tabs.Trigger
                                    value="pid"
                                    className={`px-4 py-2 ${controlTabs === "pid" ? "border-b-2 border-blue-500" : ""}`}
                                >
                                    PID
                                </Tabs.Trigger>
                                <Tabs.Trigger
                                    value="hysteresis"
                                    className={`px-4 py-2 ${controlTabs === "hysteresis" ? "border-b-2 border-blue-500" : ""}`}
                                >
                                    Histerese
                                </Tabs.Trigger>
                            </Tabs.List>
                            <Tabs.Content value="pid" className="space-y-4">
                                <div>
                                    <Label htmlFor="kp">Kp</Label>
                                    <Input
                                        id="kp"
                                        type="number"
                                        value={`${kp}`}
                                        onChange={(e) => setKp((e.target.value as unknown) as number)}
                                        step="0.001"
                                    />
                                </div>
                                <div>
                                    <Label htmlFor="ki">Ki</Label>
                                    <Input
                                        id="ki"
                                        type="number"
                                        value={`${ki}`}
                                        onChange={(e) => setKi((e.target.value as unknown) as number)}
                                        step="0.001"
                                    />
                                </div>
                                <div>
                                    <Label htmlFor="kd">Kd</Label>
                                    <Input
                                        id="kd"
                                        type="number"
                                        value={`${kd}`}
                                        onChange={(e) => setKd((e.target.value as unknown) as number)}
                                        step="0.001"
                                    />
                                </div>
                                {/* <Button onClick={() => handlePIDChanges(true)} className="w-full bg-black text-white hover:bg-gray-800">Testar</Button> */}
                                <Button onClick={() => handlePIDChanges(false)} className="w-full bg-black text-white hover:bg-gray-800">Aplicar alterações</Button>
                            </Tabs.Content>
                            <Tabs.Content value="hysteresis" className="space-y-4">
                                <div>
                                    <Label htmlFor="hh">Limiar superior</Label>
                                    <Input
                                        id="hh"
                                        type="number"
                                        value={`${hh}`}
                                        onChange={(e) => setHH((e.target.value as unknown) as number)}
                                        step="1"
                                    />
                                </div>
                                <div>
                                    <Label htmlFor="lh">Limiar inferior</Label>
                                    <Input
                                        id="lh"
                                        type="number"
                                        value={`${lh}`}
                                        onChange={(e) => setLH((e.target.value as unknown) as number)}
                                        step="1"
                                    />
                                </div>
                                <Button onClick={() => handleHysteresisChanges()} className="w-full bg-black text-white hover:bg-gray-800">Aplicar alterações</Button>
                            </Tabs.Content>
                        </Tabs.Root>
                    </Tabs.Content>

                </Tabs.Root>
            </div>
        </div>
    );
}

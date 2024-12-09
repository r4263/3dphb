import { useCallback, useEffect, useState } from "react";
import * as Tabs from "@radix-ui/react-tabs";
import * as Slider from "@radix-ui/react-slider";
import { Button } from "./components/ui/button";
import { Input } from "./components/ui/input";
import { Label } from "@radix-ui/react-label";
import * as ToggleGroup from "@radix-ui/react-toggle-group";
import { ControlModes, DeviceState, TabsOptions } from "./types/general";
import { useNotification } from "./NotificationProvider";
import { sha256 } from "js-sha256";

function getIpHash(): string {
    // const ip = window.location.hostname;
    const ip = "4.4.4.2";
    return sha256(ip);
}

export default function ControlPanel() {
    const { pushNotification } = useNotification();

    const [blockWSRefresh, setBlockWSRefresh] = useState<boolean>(false);

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


    useEffect(() => {
        const websocketUrl = `ws://4.4.4.1/ws`;
        const socket = new WebSocket(websocketUrl);

        socket.onopen = () => {
            pushNotification("Conexão websocket estabelecida!");
        };

        socket.onmessage = (event) => {
            if (!blockWSRefresh) handleComponentRefresh(JSON.parse(event.data) as DeviceState);
        };

        socket.onclose = () => {
            pushNotification("Websocket desconectado!");
        };

        socket.onerror = (error) => {
            pushNotification("Erro no websocket!");
            console.log(error);
        };

        return () => {
            socket.close();
        };
    }, []);

    const handleComponentRefresh = (data: DeviceState) => {
        if (data.kp !== kp) setKp(data.kp);
        if (data.ki !== ki) setKi(data.ki);
        if (data.kd !== kd) setKd(data.kd);
        if (data.heater_enabled !== heatingEnabled) setHeatingEnabled(data.heater_enabled);
        if (data.cpu_temp !== cpuTemperature) setCPUTemperature(data.cpu_temp);
        if (data.bed_temp !== heaterTemperature) setHeaterTemperature(data.bed_temp);
        setControlMode(data.control_mode);
        if (data.lh !== lh) setLH(data.lh);
        if (data.hh !== hh) setHH(data.hh);
        if (data.setpoint !== setpoint) setSetpoint(data.setpoint);
    };

    const handleHeaterToggle = useCallback(() => {
        setHeatingEnabled((prev) => !prev);
    }, []);

    const handleHeaterState = useCallback(async () => {
        // Fetch the IP hash
        const ipHash = await getIpHash();
        console.log(ipHash); // Log the hash to verify

        // Now send the request
        try {
            const response = await fetch("http://4.4.4.1:9000/state/set/heater", {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify({
                    token: ipHash,
                    heater_enable: !heatingEnabled,
                }),
            });

            if (response.ok) {
                const result = await response.json();
                console.log(result); // Handle success
            } else {
                console.error("Failed to toggle heater:", response.statusText);
            }
        } catch (error) {
            console.error("Error during POST request:", error);
        }
    }, [heatingEnabled]);

    return (
        <div className="flex items-center justify-center min-h-screen bg-gray-100">
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
                            <Label>Temperatura do elemento: {heaterTemperature.toFixed(2)}ºC</Label>
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
                                    onValueChange={(value) => {
                                        if (value) {
                                            setControlMode(value === "pid" ? 1 : 0);
                                        }
                                    }}
                                    className="flex space-x-2"
                                >
                                    <ToggleGroup.Item
                                        value="pid"
                                        className={`px-4 py-2 border rounded-md ${controlMode === 1 ? "bg-black text-white" : "bg-gray-200 text-black"}`}
                                    >
                                        PID
                                    </ToggleGroup.Item>
                                    <ToggleGroup.Item
                                        value="hysteresis"
                                        // onClick={}
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
                                min={30}
                                max={135}
                                step={1}
                                disabled={heatingEnabled}
                                onClick={handleHeaterState}
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
                            <Button onClick={handleHeaterState} className="w-full bg-black text-white hover:bg-gray-800">
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
                                <Button className="w-full bg-black text-white hover:bg-gray-800">Testar</Button>
                                <Button className="w-full bg-black text-white hover:bg-gray-800">Aplicar alterações</Button>
                            </Tabs.Content>
                            <Tabs.Content value="hysteresis" className="space-y-4">
                                <div>
                                    <Label htmlFor="hh">Limite superior</Label>
                                    <Input
                                        id="hh"
                                        type="number"
                                        value={`${hh}`}
                                        onChange={(e) => setHH((e.target.value as unknown) as number)}
                                        step="1"
                                    />
                                </div>
                                <div>
                                    <Label htmlFor="lh">Limite inferior</Label>
                                    <Input
                                        id="lh"
                                        type="number"
                                        value={`${lh}`}
                                        onChange={(e) => setLH((e.target.value as unknown) as number)}
                                        step="1"
                                    />
                                </div>
                                <Button className="w-full bg-black text-white hover:bg-gray-800">Aplicar alterações</Button>
                            </Tabs.Content>
                        </Tabs.Root>
                    </Tabs.Content>

                </Tabs.Root>
            </div>
        </div>
    );
}

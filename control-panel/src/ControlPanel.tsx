import { useCallback, useEffect, useState } from "react"
import * as Tabs from "@radix-ui/react-tabs"
import * as Slider from "@radix-ui/react-slider"
import { Button } from "./components/ui/button"
import { Input } from "./components/ui/input"
import { Label } from "@radix-ui/react-label"

export default function ControlPanel() {
    const [activeTab, setActiveTab] = useState("state");
    const [heaterTemperature, setHeaterTemperature] = useState(0);
    const [cpuTemperature, setCPUTemperature] = useState(0);
    const [setpoint, setSetpoint] = useState(0);
    const [heatingEnabled, setHeatingEnabled] = useState(false);
    const [kp, setKp] = useState("0.000");
    const [ki, setKi] = useState("0.000");
    const [kd, setKd] = useState("0.000");
    const [ws, setWs] = useState<any>(null);

    // Websocket handlers
    useEffect(() => {
        const websocketUrl = `ws://${window.location.host}/ws`;
        // const wsUrl = `ws://4.4.4.1/ws`;
        const socket = new WebSocket(websocketUrl);

        socket.onopen = () => {
            console.log("WebSocket connection established.");
            setWs(socket);
        };
        socket.onmessage = (event) => { console.log("Message received:", event.data); };
        socket.onclose = () => { setWs(null); };
        socket.onerror = (error) => { console.error("WebSocket error:", error); };

        return () => { socket.close(); };
    }, []);

    const handleHeaterToggle = useCallback(() => {
        setHeatingEnabled(!heatingEnabled);
    }, [])

    const handlePIDactions = useCallback(() => {

    }, []);

    return (
        <div className="flex items-center justify-center min-h-screen bg-gray-100">
            <div className="w-full max-w-md p-6 bg-white rounded-lg shadow-lg">
                <Tabs.Root value={activeTab} onValueChange={setActiveTab}>
                    <Tabs.List className="flex mb-4 border-b">
                        <Tabs.Trigger
                            value="state"
                            className={`px-4 py-2 ${activeTab === "state" ? "border-b-2 border-blue-500" : ""
                                }`}
                        >
                            Estado
                        </Tabs.Trigger>
                        <Tabs.Trigger
                            value="pid"
                            className={`px-4 py-2 ${activeTab === "pid" ? "border-b-2 border-blue-500" : ""
                                }`}
                        >
                            Configurações PID
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
                            <Label>Temperatura do elemento: {heaterTemperature}ºC</Label>
                            <div className="w-full bg-gray-200 rounded-full h-2.5">
                                <div
                                    className="bg-blue-600 h-2.5 rounded-full"
                                    style={{ width: `${((heaterTemperature - 30) / 70) * 100}%` }}
                                ></div>
                            </div>
                        </div>
                        <div>
                            <Label>Ajuste de temperatura</Label>
                            <div className="relative pt-8">
                                <Slider.Root
                                    className="relative flex items-center select-none touch-none w-full h-5"
                                    value={[setpoint]}
                                    onValueChange={(newValue) => setSetpoint(newValue[0])}
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
                                <div className="absolute inset-0 flex items-center justify-center pointer-events-none">
                                    <span className="text-lg font-semibold">{setpoint}ºC</span>
                                </div>
                            </div>
                        </div>

                        <div className="flex items-center space-x-2">
                            <Button onClick={handleHeaterToggle} id="heating" className="w-full">Salvar</Button>
                        </div>
                    </Tabs.Content>

                    <Tabs.Content value="pid" className="space-y-4">
                        <div>
                            <Label htmlFor="kp">Kp</Label>
                            <Input
                                id="kp"
                                type="number"
                                value={kp}
                                onChange={(e) => setKp(e.target.value)}
                                step="0.001"
                            />
                        </div>
                        <div>
                            <Label htmlFor="ki">Ki</Label>
                            <Input
                                id="ki"
                                type="number"
                                value={ki}
                                onChange={(e) => setKi(e.target.value)}
                                step="0.001"
                            />
                        </div>
                        <div>
                            <Label htmlFor="kd">Kd</Label>
                            <Input
                                id="kd"
                                type="number"
                                value={kd}
                                onChange={(e) => setKd(e.target.value)}
                                step="0.001"
                            />
                        </div>
                        <Button className="w-full">Testar</Button>
                        <Button className="w-full">Salvar</Button>
                    </Tabs.Content>
                </Tabs.Root>
            </div>
        </div>
    )
}


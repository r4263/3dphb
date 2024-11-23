import styles from '../styles/Main.module.css'
import { Host, Info } from '../interfaces/global'
import { KeyRound, Lock, LockOpen, ShieldQuestion, Unplug, Wifi, WifiHigh, WifiLow, WifiOff, WifiZero } from 'lucide-react';
import { EncryptionType, SignalStrength } from '../types/global';
import { ReactElement, useEffect, useState } from 'react';
import { Button } from 'antd';
import { Input } from 'antd';

function signalStrengthToText(strength: number): SignalStrength {
    if (strength <= -70) return 'Fraco';
    if (strength > -70 && strength <= -60) return 'Razoável';
    if (strength > -60 && strength <= -50) return 'Bom';

    if (strength > -50) return 'Excelente';
    return 'Desconhecido';
}

function EncryptionIcon({ encryption }: { encryption: EncryptionType }): ReactElement {
    switch (encryption) {
        case 'OPEN': return (<LockOpen />);
        case 'UNKNOWN': return (<ShieldQuestion />);
        default: return (<Lock />);
    }

}

function SignalIcon({ strength }: { strength: SignalStrength }): ReactElement {
    switch (strength) {
        case 'Excelente': return (<Wifi />);
        case 'Bom': return (<WifiHigh />);
        case 'Razoável': return (<WifiLow />);
        case 'Fraco': return (<WifiZero />);
        case 'Desconhecido': return (<WifiOff />)
    }
}

export default function Main({ hostList, devInfo, selectedItem, setSelectedItem }: { hostList: Host[], devInfo: Info, selectedItem: number | undefined, setSelectedItem: React.Dispatch<React.SetStateAction<number | undefined>> }) {

    const [isRequestingServer, setIsRequestingServer] = useState<boolean>(false);

    const handleSelectionChange = (index: number) => { if (index !== selectedItem) setSelectedItem(index) }

    useEffect(() => {
        if (selectedItem !== undefined) {
            document.getElementById(`${selectedItem}-${hostList[selectedItem].ssid}`)?.scrollIntoView({
                behavior: 'smooth',
                block: 'center'
            })
        }
    }, [selectedItem]);


    return (
        <div className={styles.container}>
            <div className={styles.headerBox}>
                <span className={styles.headerTitle}>Configurações de rede</span>
                <span className={styles.headerSecondary}>Host: {devInfo.hostname}</span>
                <span className={styles.headerSecondary}>Endereço IP: {devInfo.hostIP}</span>
            </div>
            <div key='itemList' id='itemList' className={`${styles.listContainer} ${selectedItem !== undefined ? styles.blockScrolling : ''}`}>
                {hostList.map((e, index) => {

                    const strength: SignalStrength = signalStrengthToText(e.rssi);
                    const isItemSelected: boolean = selectedItem === index;
                    const itemId: string = `${index}-${e.ssid}`;

                    return (
                        <>
                            <span key={itemId} id={itemId} onClick={() => handleSelectionChange(index)} className={`${styles.item} ${isItemSelected ? styles.selected : ''}`}>
                                <div className={styles.header}>
                                    <span>
                                        <span className={styles.title}>{e.ssid}</span>
                                        <span className={styles.secondary}>{e.mac_address}</span>
                                    </span>
                                    <div className={styles.status}>
                                        <SignalIcon strength={strength} />
                                        <EncryptionIcon encryption={e.encryption} />
                                    </div>
                                </div>
                                <div style={{ color: isItemSelected ? 'white' : '' }} className={styles.secondaryContainer}>
                                    <span className={isItemSelected ? styles.secondarySelected : styles.secondaryUnselected}>{signalStrengthToText(e.rssi)}(<b>{e.rssi}dBm</b>)</span>
                                    <span className={isItemSelected ? styles.secondarySelected : styles.secondaryUnselected}>Canal {e.channel}</span>
                                    <span className={isItemSelected ? styles.secondarySelected : styles.secondaryUnselected}><b>{e.encryption}</b></span>
                                </div>
                                <div
                                    style={{
                                        maxHeight: isItemSelected ? '200px' : '0px',
                                        display: isItemSelected ? 'flex' : 'none'
                                    }}
                                    className={styles.collapsible}
                                >
                                    <div className={styles.passwordField}>
                                        {e.encryption !== "OPEN" ? <Input.Password size="middle" placeholder="Informe a senha" prefix={<KeyRound />} /> : <span>Esta rede não possui senha!</span>}
                                    </div>
                                    <div className={styles.actionButtons}>
                                        <Button type="primary" style={{ color: 'inherit' }} danger disabled={isRequestingServer} onClick={() => setSelectedItem(undefined)}>
                                            Cancelar
                                        </Button>
                                        <Button
                                            type="primary"
                                            icon={<Unplug />}
                                            loading={isRequestingServer}
                                            onClick={() => { setIsRequestingServer(true) }}
                                        >
                                            Enviar ao dispositivo
                                        </Button>
                                    </div>

                                </div>
                            </span>

                            {index < hostList.length - 1 && <span className={styles.divider} />}
                        </>
                    )
                })}
            </div>
        </div>
    )
}
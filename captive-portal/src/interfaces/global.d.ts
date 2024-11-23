import { EncryptionType } from "../types/global"

interface Host {
    ssid: string,
    rssi: number,
    encryption: EncryptionType,
    mac_address: string
    channel: number
}

interface Info {
    hostIP: string,
    hostname: string,
    hostPassword?: string,
}

export { Host, Info, MappingValues }
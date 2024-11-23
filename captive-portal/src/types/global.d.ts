type BackgroundColors = 'Dark' | 'Greenie' | 'Bluish' | 'Jasper';

type ValueMappings = {
    name: BackgroundColors,
    circle: string,
    background: string
}

type SignalStrength = 'Desconhecido' | 'Fraco' | 'Razoável' | 'Bom' | 'Excelente';

type EncryptionType = 'OPEN' | 'WEP' | 'WPA' | 'WPA2' | 'WPA+WPA2' | 'WPA2-EAP' | 'WPA3' | 'WPA2+WPA3' | 'WAPI' | 'UNKNOWN';

export { BackgroundColors, ValueMappings, SignalStrength, EncryptionType }
import { useEffect, useState } from "react";
import Main from "./Main";
import Notification from "./Notification";
import { Info, Host } from "../interfaces/global";
import styles from "../styles/App.module.css"
import BgColorToggler from "./BgColorToggler";
import { BackgroundColors } from "../types/global";
import { colorMapping } from "../constants";

async function fetchData(url: string, method: "GET" | "POST", body?: {}) {
  const response = await fetch(url, { method: method });
  return response.json();
}

const initialState: { devInfo: Info, hosts: Host[] } = {
  devInfo: {
    hostname: 'phb-ctrl',
    hostIP: 'Desconhecido',
    hostPassword: 'Desconhecido'
  },
  hosts: []
}

export default function App() {

  const [pageTitle, setPageTitle] = useState<string>("phb-ctrl");
  const [isLoadingDeviceInfo, setIsLoadingDeviceInfo] = useState<boolean>(true);
  const [deviceInfo, setDeviceInfo] = useState<Info>(initialState.devInfo);
  const [isLoadingHosts, setIsLoadingHosts] = useState<boolean>(true);
  const [hosts, setHosts] = useState<Host[]>(initialState.hosts);

  const [collapse, setCollapse] = useState<boolean>(true);
  const [activeSelection, setActiveSelection] = useState<boolean>(false);
  const [bgColor, setBgColor] = useState<BackgroundColors>('Dark');

  const [selectedItem, setSelectedItem] = useState<number | undefined>(undefined)

  document.title = pageTitle;

  useEffect(() => {
    fetchData("http://10.0.0.249:4444/device-info", "GET")
      .then(r => {
        setDeviceInfo(r);
        setIsLoadingDeviceInfo(false);
      })
      .catch(err => {
        console.log(err);
        // err
      });

    fetchData("http://10.0.0.249:4444/hosts", "GET")
      .then(r => {
        setHosts(r);
        setIsLoadingHosts(false);
      })
      .catch(err => {
        console.log(err);
        // err
      })
  }, []);

  useEffect(() => {
    if (hosts.length && deviceInfo.hostIP !== "Desconhecido") {
      setPageTitle(`${deviceInfo.hostname} - ${deviceInfo.hostIP}`);
    }
  }, [isLoadingDeviceInfo, isLoadingHosts]);

  useEffect(() => {
    setActiveSelection((selectedItem === undefined));
  }, [selectedItem])
  // useEffect(() => {
  //   setActiveSelection((selectedItem !== undefined || collapse));
  // }, [selectedItem, collapse])

  useEffect(() => { console.log(activeSelection) }, [activeSelection])

  return (
    <div style={{ backgroundImage: colorMapping.find(e => e.name === bgColor)?.background }} className={styles.background}>
      <Notification />
      <BgColorToggler
        isBgActive={activeSelection}
        setCollapse={setCollapse}
        collapse={collapse}
        setBgColor={setBgColor}
      />
      <Main
        hostList={hosts}
        devInfo={deviceInfo}
        selectedItem={selectedItem}
        setSelectedItem={setSelectedItem}
      />
      <div
        style={{
          display: activeSelection ? 'none' : 'flex',
          opacity: activeSelection ? 0 : 1
        }}
        className={styles.darkBg} />
    </div >
  );
}
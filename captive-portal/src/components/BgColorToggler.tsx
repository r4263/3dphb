import { Palette } from 'lucide-react'
import styles from '../styles/Toggler.module.css'
import { BackgroundColors } from '../types/global'
import { colorMapping } from '../constants'
import React, { useEffect, useState } from 'react'

export default function BgColorToggler(
    {
        isBgActive,
        collapse,
        setCollapse,
        setBgColor
    }: {
        isBgActive: boolean,
        collapse: boolean,
        setCollapse: React.Dispatch<React.SetStateAction<boolean>>
        setBgColor: React.Dispatch<React.SetStateAction<BackgroundColors>>,
    }
) {

    const active: boolean = isBgActive && !collapse;

    return (
        <div
            className={styles.container}>
            <span className={styles.iconButton}>
                <Palette onClick={() => { setCollapse(!collapse) }} className={styles.icon} />
            </span>
            <div style={{ maxWidth: collapse ? '0px' : '200px' }} className={styles.collapsible}>
                {colorMapping.map(e => {
                    return (
                        <span onClick={() => setBgColor(e.name)} key={e.name} className={styles.item}>
                            <div style={{ backgroundColor: e.circle }} className={styles.circle}>
                                <span style={{ zIndex: 100 }}>{e.name}</span>
                            </div>
                        </span>
                    )
                })}
            </div>
        </div>
    )
}
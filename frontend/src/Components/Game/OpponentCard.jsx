import React, { useMemo } from 'react'
import { Avatar } from 'primereact/avatar';
import { getRandomColor } from '../../Util/random';
import { countOccurrences } from '../../Util/array';
import styles from './Styles/opponentcard.module.css';

export const OpponentCard = (props) => {
    const color = useMemo(() => getRandomColor(), []);

    if (props.waiting) {
        return (
            <div className={styles.container} >
                <h1>Room ID: {props.roomID} </h1>
                <h1>Waiting for opponent...</h1>
            </div>
        )
    }

    if (props.timeOut) {
        return (
            <div className={styles.container} >
                <h1>Time out</h1>
            </div>
        )
    }

    const label = props.firstName[0]?.toUpperCase() + props.lastName[0]?.toUpperCase();

    return (
        <div className={styles.container} >
            <h1 className={styles.title} > Opponent </h1>
            <div className={styles.left_row} >
                <Avatar label={label} size='large'
                    shape='circle' className={styles.avatar}
                    style={{ backgroundColor: color }} />
                <div className={styles.column} >
                    <h1> {props.firstName + ' ' + props.lastName} </h1>
                    <h2> {props.username} </h2>
                </div>
            </div>
            <div className={styles.center_row} >
                <div>
                    <Avatar label={`${countOccurrences(props.template, '+')}`} size='large'
                        shape='circle' className={styles.avatar}
                        style={{ backgroundColor: '#B1B2FF' }} />
                    <h2>correct place</h2>
                </div>
                <div>
                    <Avatar label={`${countOccurrences(props.template, '-')}`} size='large'
                        shape='circle' className={styles.avatar}
                        style={{ backgroundColor: '#6191ff' }} />
                    <h2>correct character</h2>
                </div>
            </div>
        </div>
    )
}

export default OpponentCard;
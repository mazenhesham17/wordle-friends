import React from 'react';
import styles from './Styles/card.module.css';

export const Card = (props) => {
    return (
        <div className={styles.container} >
            <h1 className={styles.title} >
                {props.title}
            </h1>
            <div className={styles.row} >
                <div className={styles.value}>
                    {props.value ?
                        <h3>
                            {props.value}
                        </h3>
                        :
                        <div className={styles.row}>
                            <h3 className={styles.win} >
                                {props.wins}
                            </h3>
                            <h3>
                                /
                            </h3>
                            <h3 className={styles.lose}>
                                {props.loses}
                            </h3>
                        </div>
                    }
                </div>
                <div className={styles.value}>
                    <h3>
                        {props.unit}
                    </h3>
                </div>
            </div>
        </div>
    )
}

export default Card;
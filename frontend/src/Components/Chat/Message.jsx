import React from 'react'
import styles from './Styles/chat.module.css';

export const Message = (props) => {
    return (
        <div className={`${styles.message_conatiner} ${props.sender ? styles.sender : styles.receiver} `}>
            <p className={styles.content} > {props.message} </p>
            <p className={styles.time} > {props.time} </p>
        </div>
    )
}

export default Message;
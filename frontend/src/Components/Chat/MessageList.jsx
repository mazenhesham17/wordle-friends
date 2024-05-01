import React, { useEffect, useRef } from 'react';
import styles from './Styles/chat.module.css';
import Message from './Message';
import { formatTime, getDateLabel, formatDateInClientTimeZone } from '../../Util/date';



export const MessageList = (props) => {
    let prevDate = null;

    const listRef = useRef(null);

    useEffect(() => {
        if (listRef.current) {
            listRef.current.scrollTo({
                top: listRef.current.scrollHeight,
                behavior: (listRef.current.scrollTop === 0 ? 'instant' : 'smooth'),
            });
        }
    }, [props.messages]);

    return (
        <div className={styles.body} ref={listRef} >
            {
                props.messages.map((message, index) => {
                    const currentDate = new Date(formatDateInClientTimeZone(message.sendTime)).toDateString();
                    const show = !prevDate || currentDate !== prevDate;
                    prevDate = currentDate;
                    return (
                        <React.Fragment key={index}>
                            {show && <p className={styles.label} > {getDateLabel(message.sendTime)} </p>}
                            <Message sender={message.playerID != props.friendID} message={message.message} time={formatTime(message.sendTime)} />
                        </React.Fragment>
                    )
                })
            }
        </div>
    )
}

export default MessageList;
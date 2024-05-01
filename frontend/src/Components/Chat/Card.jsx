import React from 'react'
import { Avatar } from 'primereact/avatar';
import { useDispatch } from 'react-redux';
import { changeChat } from '../../State/chatSlice';
import styles from './Styles/list.module.css';
import { getLabel } from '../../Util/string';


export const Card = (props) => {
    const dispatch = useDispatch();
    const label = getLabel(props.firstName, props.lastName);

    return (
        <div className={styles.card} onClick={() => {
            dispatch(changeChat(props));
        }} >
            <Avatar label={label} size='large'
                shape='circle' className={styles.avatar}
                style={{ backgroundColor: props.color }} />
            <p className={props.read ? null : styles.unread} > {props.firstName + ' ' + props.lastName} </p>
        </div>
    )
}

export default Card;
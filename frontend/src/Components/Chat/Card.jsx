import React from 'react'
import { useDispatch } from 'react-redux';
import { changeChat } from '../../State/chatSlice';
import { Avatar } from 'primereact/avatar';
import { getLabel } from '../../Util/string';
import styles from './Styles/list.module.css';


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
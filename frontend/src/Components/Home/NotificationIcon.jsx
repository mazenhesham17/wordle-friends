import React, { useEffect, useState, useContext } from 'react'
import styles from './Styles/sidebar.module.css';
import { useSelector, useDispatch } from 'react-redux';
import { addUnseenChat, clear, changeMessage } from '../../State/chatSlice';
import { Link } from 'react-router-dom';
import { FunctionContext } from '../../App';
import { generateSocketUrl, generateUrl } from '../../Util/urls';


export const NotificationIcon = (props) => {
    const token = localStorage.getItem('token');
    const dispatch = useDispatch();
    const showErrorMessage = useContext(FunctionContext);
    const pageName = useSelector(state => state.page.name);
    const unseenChats = useSelector(state => state.chat.unseenChats);
    const [ID, setID] = useState(null);
    const [flag, setFlag] = useState(false);
    const [completed, setCompleted] = useState(false);
    const [ws, updateWS] = useState(null);

    const connectToServer = async () => {
        try {
            const url = generateUrl('chat', 'notification');
            const response = await fetch(url, {
                method: 'Post',
                headers: {
                    'Authorization': token
                },
            });
            const responseJSON = await response.json();
            if (responseJSON.error) {
                showErrorMessage(responseJSON.error);
                return;
            }
            setCompleted(true);
        } catch ({ name, message }) {
            showErrorMessage(message);
        }
    }


    const createSocket = () => {
        const webSocket = new WebSocket(generateSocketUrl());
        updateWS(webSocket);
        webSocket.onopen = () => {
            console.log('WebSocket Client Connected');
        };
        webSocket.onmessage = socketOnMessage;
        webSocket.onclose = () => {
            console.log('WebSocket Client Disconnected');
        };
    }


    const socketOnMessage = (message) => {
        const response = message.data;
        if (response.startsWith('P : ')) {
            setID(response.split(' ')[2]);
            setFlag(true);
        }
    }


    const closeSocket = () => {
        if (ws)
            ws.close();
    }

    useEffect(() => {
        if (!flag) return;
        if (pageName !== props.title) {
            dispatch(addUnseenChat(ID));
        } else {
            dispatch(changeMessage(ID));
        }
        setFlag(false);
    }, [flag])


    useEffect(() => {
        if (pageName === props.title) {
            dispatch(clear());
        }

    }, [pageName]);


    useEffect(() => {
        connectToServer();
    }, []);

    useEffect(() => {
        if (completed) {
            createSocket();
        }
        return () => {
            closeSocket();
        }
    }, [completed]);


    return (
        <Link to={`/${props.title}`} className={`${styles.container} ${styles.item} ${pageName === props.title ? styles.active : ''}`} >
            <div className={styles.notification_container} >
                {unseenChats.length > 0 &&
                    <div className={styles.notification} >
                        {unseenChats.length < 10 ? unseenChats.length : '9+'}
                    </div>}
                <box-icon name={props.name} size="md" color='#B1B2FF' ></box-icon>
            </div>
            <h2>{props.title}</h2>
        </Link>
    )
}

export default NotificationIcon;
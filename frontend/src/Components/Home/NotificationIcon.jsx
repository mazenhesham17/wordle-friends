import React, { useEffect, useState, useContext } from 'react'
import styles from './Styles/sidebar.module.css';
import { useSelector, useDispatch } from 'react-redux';
import { addUnseenChat, clear, changeMessage } from '../../State/chatSlice';
import { Link } from 'react-router-dom';
import { FunctionContext } from '../../App';


export const NotificationIcon = (props) => {
    const token = localStorage.getItem('token');
    const showErrorMessage = useContext(FunctionContext);
    const dispatch = useDispatch();
    const pageName = useSelector(state => state.page.name);
    const [ID, setID] = useState(null);
    const [flag, setFlag] = useState(false);
    const unseenChats = useSelector(state => state.chat.unseenChats);
    const [completed, setCompleted] = useState(false);
    const [ws, updateWS] = useState(null);

    const connectToServer = async () => {
        try {
            const response = await fetch('http://localhost:4000/api/chat/notification', {
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
        const webSocket = new WebSocket('ws://localhost:8080');
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
        <div className={`${styles.container} ${pageName === props.title ? styles.active : ''} `} >
            <Link to={`/${props.title}`} >
                <div className={styles.notification_container} >
                    {unseenChats.length > 0 &&
                        <div className={styles.notification} >
                            {unseenChats.length < 10 ? unseenChats.length : '9+'}
                        </div>}
                    <box-icon name={props.name} size="md" color='#B1B2FF' ></box-icon>
                </div>
            </Link>
            <h2>{props.title}</h2>
        </div>
    )
}

export default NotificationIcon;
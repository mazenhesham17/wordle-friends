import React, { useState, useEffect, useContext } from 'react'
import { FunctionContext } from '../../App';
import { useSelector, useDispatch } from 'react-redux';
import { changeChat } from '../../State/chatSlice';
import styles from './Styles/chat.module.css';
import { Avatar } from 'primereact/avatar';
import { getLabel } from '../../Util/string';
import MessageList from './MessageList';

export const Chat = () => {
    const token = localStorage.getItem('token');
    const showErrorMessage = useContext(FunctionContext);
    const chatDetails = useSelector(state => state.chat.activeChat);
    const dispatch = useDispatch();

    const [roomID, setRoomID] = useState('');
    const [messages, setMessages] = useState([]);

    const [sentMessage, setSentMessage] = useState('');
    const [receivedMessage, setReceivedMessage] = useState('');

    const [WS, setWS] = useState(null);
    const [loading, setLoading] = useState(true);
    const [waiting, setWaiting] = useState(false);
    const [flag, setFlag] = useState(false);

    useEffect(() => {
        return () => {
            dispatch(changeChat(null));
        }
    }, []);

    const resetConnection = () => {
        setRoomID('');
        setMessages([]);
        setSentMessage('');
        setReceivedMessage('');
        setWS(null);
        setLoading(true);
        setWaiting(false);
        setFlag(false);
    }

    const fetchRoom = async () => {
        try {
            const response = await fetch(`http://localhost:4000/api/chat/room/${chatDetails.friendID}`, {
                method: 'GET',
                headers: {
                    'Authorization': token
                }
            });
            const responseJSON = await response.json();
            if (responseJSON.error) {
                showErrorMessage(responseJSON.error);
                return;
            }
            setRoomID(responseJSON.roomID);
        } catch ({ name, message }) {
            showErrorMessage(message);
        }
    }

    // get old messages from API
    const fetchMessages = async () => {
        try {
            const chatID = roomID.split('C')[1];
            const response = await fetch(`http://localhost:4000/api/chat/${chatID}`, {
                method: 'GET',
                headers: {
                    'Authorization': token
                }
            });
            const responseJSON = await response.json();
            if (responseJSON.error) {
                showErrorMessage(responseJSON.error);
                return;
            }
            setMessages(responseJSON.messages);
        } catch ({ name, message }) {
            showErrorMessage(message);
        }
    }

    // open socket connection
    const connectRoom = async () => {
        try {
            const response = await fetch(`http://localhost:4000/api/chat/start/${roomID}`, {
                method: 'POST',
                headers: {
                    'Authorization': token
                }
            });
            const responseJSON = await response.json();
            if (responseJSON.error) {
                showErrorMessage(responseJSON.error);
                return;
            }
            setWaiting(true);
        } catch ({ name, message }) {
            showErrorMessage(message);
        }
    }

    // get roomID from API
    useEffect(() => {
        if (chatDetails != null) {
            resetConnection();
            fetchRoom();
        }
        return () => {
            closeSocket();
        }
    }, [chatDetails]);

    useEffect(() => {
        if (roomID) {
            fetchMessages();
            connectRoom();
        }
    }, [roomID]);

    useEffect(() => {
        if (waiting) {
            createSocket();
        }

        return () => {
            closeSocket();
        }
    }, [waiting])

    const updateWS = (ws) => {
        setWS(ws);
    }

    const socketOnMessage = (message) => {
        const response = message.data;
        setReceivedMessage(response);
        toggleFlag();
    }

    const sendMessage = () => {
        WS.send(sentMessage);
        setSentMessage('');
    }

    const seenMessage = () => {
        WS.send("$M$W%B%");
    }

    const closeSocket = () => {
        if (WS)
            WS.close();
    }

    const createSocket = () => {
        const webSocket = new WebSocket('ws://localhost:8080');
        updateWS(webSocket);
        webSocket.onopen = () => {
            console.log('WebSocket Client Connected');
            setLoading(false);
        };
        webSocket.onmessage = socketOnMessage;
        webSocket.onclose = () => {
            console.log('WebSocket Client Disconnected');
        };
    }

    const updateMessage = (e) => {
        setSentMessage(e.target.value);
    }

    const toggleFlag = () => {
        setFlag(!flag);
    }

    const reset = () => {
        setReceivedMessage('');
        toggleFlag();
    }

    useEffect(() => {
        if (flag) {
            const parsedMessage = JSON.parse(receivedMessage);
            appendToMessages(parsedMessage);
            if (parsedMessage.playerID == chatDetails.friendID) {
                seenMessage();
            }
            reset();
        }
    }, [flag]);

    const appendToMessages = (message) => {
        setMessages((messages) => [...messages, message]);
    }

    return (
        <div className={styles.container} >
            {
                chatDetails == null ? <p>Select a friend to chat with</p>
                    :
                    <>
                        <div className={styles.heading} >
                            <Avatar label={getLabel(chatDetails.firstName, chatDetails.lastName)} size='large'
                                shape='circle' className={styles.avatar}
                                style={{ backgroundColor: chatDetails.color }} />
                            <p > {chatDetails.firstName + ' ' + chatDetails.lastName} </p>
                        </div>
                        {messages.length > 0 && <MessageList messages={messages} friendID={chatDetails.friendID} />}
                        <div className={styles.input} >
                            <input type="text" value={sentMessage} placeholder="Type a message" onChange={updateMessage} />
                            <button onClick={sendMessage} disabled={loading || sentMessage.length === 0}>
                                <box-icon name='send' color='white'></box-icon>
                            </button>
                        </div>
                    </>
            }
        </div>
    )
}

export default Chat;
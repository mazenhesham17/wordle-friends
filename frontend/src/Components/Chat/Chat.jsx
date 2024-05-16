import React, { useState, useEffect, useContext } from 'react'
import { useSelector, useDispatch } from 'react-redux';
import { changeChat } from '../../State/chatSlice';
import { FunctionContext } from '../../App';
import { Avatar } from 'primereact/avatar';
import { getLabel } from '../../Util/string';
import MessageList from './MessageList';
import styles from './Styles/chat.module.css';

export const Chat = () => {
    const token = localStorage.getItem('token');
    const dispatch = useDispatch();
    const showErrorMessage = useContext(FunctionContext);
    const chatDetails = useSelector(state => state.chat.activeChat);

    const [messages, setMessages] = useState([]);
    const [sentMessage, setSentMessage] = useState('');
    const [receivedMessage, setReceivedMessage] = useState('');

    const [WS, setWS] = useState(null);
    const [loading, setLoading] = useState(true);
    const [flag, setFlag] = useState(false);

    const appendToMessages = (message) => {
        setMessages((messages) => [...messages, message]);
    }

    const updateWS = (ws) => {
        setWS(ws);
    }

    const socketOnMessage = (message) => {
        const response = message.data;
        setReceivedMessage(response);
        toggleFlag();
    }

    const sendMessage = (e) => {
        e.preventDefault();
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

    const resetConnection = () => {
        setMessages([]);
        setSentMessage('');
        setReceivedMessage('');
        setWS(null);
        setLoading(true);
        setFlag(false);
    }

    const fetchRoom = () => {
        return new Promise(async (resolve, reject) => {
            try {
                const response = await fetch(`http://localhost:4000/api/chat/room/${chatDetails.friendID}`, {
                    method: 'GET',
                    headers: {
                        'Authorization': token
                    }
                });
                const responseJSON = await response.json();
                if (responseJSON.error) {
                    reject(responseJSON.error);
                    showErrorMessage(responseJSON.error);
                    return;
                }
                resolve(responseJSON.roomID);
            } catch ({ name, message }) {
                reject(message);
            }
        });

    }

    // get old messages from API
    const fetchMessages = async (roomID) => {
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
    const connectRoom = (roomID) => {
        return new Promise(async (resolve, reject) => {

            try {
                const response = await fetch(`http://localhost:4000/api/chat/start/${roomID}`, {
                    method: 'POST',
                    headers: {
                        'Authorization': token
                    }
                });
                const responseJSON = await response.json();
                if (responseJSON.error) {
                    reject(responseJSON.error);
                    return;
                }
                resolve(true);
            } catch ({ name, message }) {
                reject(message);
            }
        });
    }

    useEffect(() => {
        return () => {
            dispatch(changeChat(null));
        }
    }, []);

    // get roomID from API
    useEffect(() => {
        if (chatDetails == null) return;

        resetConnection();
        fetchRoom()
            .then((roomID) => {
                fetchMessages(roomID);
                connectRoom(roomID)
                    .then(() => {
                        createSocket();
                    })
                    .catch((error) => {
                        showErrorMessage(error);
                    });
            })
            .catch((error) => {
                showErrorMessage(error);
            });

        return () => {
            closeSocket();
        }
    }, [chatDetails]);

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


    return (
        <div className={`${styles.container} ${chatDetails != null ? styles.up : ''}`} >
            {
                chatDetails == null ? <p>Select a friend to chat with</p>
                    :
                    <>
                        <div className={styles.heading} >
                            <button className={styles.back} onClick={() => dispatch(changeChat(null))}  >
                                <box-icon name='arrow-back' size="2x" color="#B1B2FF"></box-icon>
                            </button>
                            <Avatar label={getLabel(chatDetails.firstName, chatDetails.lastName)} size='large'
                                shape='circle' className={styles.avatar}
                                style={{ backgroundColor: chatDetails.color }} />
                            <p > {chatDetails.firstName + ' ' + chatDetails.lastName} </p>
                        </div>
                        {messages.length > 0 && <MessageList messages={messages} friendID={chatDetails.friendID} />}
                        <form className={styles.input} onSubmit={sendMessage} >
                            <input type="text" value={sentMessage} placeholder="Type a message" onChange={updateMessage} />
                            <button type='submit' disabled={loading || sentMessage.length === 0}>
                                <box-icon name='send' color='white'></box-icon>
                            </button>
                        </form>
                    </>
            }
        </div>
    )
}

export default Chat;
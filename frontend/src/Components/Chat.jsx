import React, { useState, useEffect, useRef } from 'react'
import Message from './Message';

export const Chat = (props) => {
    const token = localStorage.getItem('token');
    const [message, setMessage] = useState('');
    const [receivedMessage, setReceivedMessage] = useState('');
    const [messages, setMessages] = useState([]);
    const [data, setData] = useState({});
    const [roomID, setRoomID] = useState('');
    const [error, setError] = useState('');
    const [WS, setWS] = useState(null);
    const [loading, setLoading] = useState(true);
    const [flag, setFlag] = useState(false);

    const fetchRoom = async () => {
        const response = await fetch(`http://localhost:4000/chat-room/${props.friendID}`, {
            method: 'GET',
            headers: {
                'Authorization': token
            }
        });
        const temp = await response.json();
        if (temp.error) {
            setError(temp.error);
            return;
        }
        setData(temp);
        setRoomID(temp.roomID);
        console.log("Fetched room")
    }

    // get roomID from API
    useEffect(() => {
        if (props.friendID) {
            fetchRoom();
        }
        return () => {
            closeSocket();
        }
    }, [props.friendID]);

    // get old messages from API
    const fetchMessages = async () => {
        const chatID = roomID.split('C')[1];
        const response = await fetch(`http://localhost:4000/chat/${chatID}`, {
            method: 'GET',
            headers: {
                'Authorization': token
            }
        });
        const temp = await response.json();
        if (temp.error) {
            setError(temp.error);
            return;
        }
        setMessages(temp);
    }

    // open socket connection
    const connectRoom = async () => {
        const response = await fetch(`http://localhost:4000/start-chat/${roomID}`, {
            method: 'POST',
            headers: {
                'Authorization': token
            }
        });
        const temp = await response.json();
        if (temp.error) {
            setError(temp.error);
            return;
        }
        setData(temp);
    }

    const updateWS = (ws) => {
        setWS(ws);
    }

    const socketOnMessage = (message) => {
        const response = message.data;
        setReceivedMessage(response);
        toggleFlag();
    }

    const sendMessage = () => {
        WS.send(message);
        setMessage('');
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
        setMessage(e.target.value);
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
            appendToMessages(JSON.parse(receivedMessage));
            console.log(messages);
            reset();
        }
    }, [flag]);

    const appendToMessages = (message) => {
        setMessages((messages) => [...messages, message]);
    }

    useEffect(() => {
        if (data.roomID) {
            fetchMessages();
            connectRoom();
        }
        if (data.message) {
            createSocket();
        }
        return () => {
            closeSocket();
        }
    }, [data]);

    const scrollContainerRef = useRef();

    useEffect(() => {
        const scrollContainer = scrollContainerRef.current;
        if (scrollContainer) {
            const latestMessage = scrollContainer.lastElementChild;
            if (latestMessage) {
                latestMessage.scrollIntoView({ behavior: 'smooth' });
            }
        }
    }, [messages]);

    return (
        props.friendID ?
            <div style={{ width: "500px", backgroundColor: "grey" }}>
                {error ? <div>{error}</div> : null}
                {loading ? <div>Loading...</div> : null}
                <h1> Chat </h1>
                <div ref={scrollContainerRef} style={{ overflow: "auto", height: "800px" }}>
                    {
                        messages.map((message, index) => {
                            return (
                                <Message key={index} sender={message.playerID != props.friendID} message={message.message} time={message.sendTime} />
                            )
                        })
                    }
                </div>
                <div>
                    <input type="text" value={message} placeholder="Type a message" onChange={updateMessage} />
                    <button onClick={sendMessage} disabled={loading}>Send</button>
                </div>
            </div> : <h1>Select a friend to chat with</h1>
    )
}

export default Chat;
import React, { useEffect, useState } from 'react'
import { useParams } from 'react-router-dom';

export const DuoGamePage = () => {
    const [WS, setWS] = useState(null);
    const [data, setData] = useState({});
    const [word, setWord] = useState('');
    const [template, setTemplate] = useState('');
    const [history, setHistory] = useState([]);
    const [flag, setFlag] = useState(false);
    const [finsihed, setFinished] = useState(false);
    const [waiting, setWaiting] = useState(true);
    const [timeout, setTimeout] = useState(false);
    const [won, setWon] = useState(false);
    const [opponentTemplate, setOpponentTemplate] = useState('');
    const [roomID, setRoomID] = useState('');
    const { urlRoomID } = useParams();

    useEffect(() => {
        console.log(urlRoomID);
        if (urlRoomID) {
            setRoomID(urlRoomID);
        }
        else {
            newGame();
        }
        window.addEventListener('beforeunload', handleBeforeUnload);
        return () => {
            window.removeEventListener('beforeunload', handleBeforeUnload);
        };
    }, [urlRoomID]);


    const updateWord = (e) => {
        setWord(e.target.value);
    }

    const updateTemplate = (template) => {
        setTemplate(template);
    }

    const toggleFlag = () => {
        setFlag(!flag);
    }

    const updateWS = (ws) => {
        setWS(ws);
    }

    const finishGame = (won) => {
        setFinished(true);
        setWon(won);
    }

    const pushOnHistory = (row) => {
        setHistory((history) => [...history, row]);
    }

    const resetRow = () => {
        setWord('');
        setTemplate('');
    }

    const token = localStorage.getItem('token');

    const socketOnMessage = (message) => {
        const response = message.data;
        if (response.startsWith('Result: ')) {
            updateTemplate(response.split(' ')[1]);
            toggleFlag();
        } else if (response.startsWith('Opponent')) {
            setOpponentTemplate(response.split(' ')[2]);
        } else {
            if (response.includes('win')) {
                finishGame(true);
            } else if (response.includes('lose')) {
                finishGame(false);
            } else {
                if (response.includes('start')) {
                    setWaiting(false);
                } else if (response === 'Time out!') {
                    setTimeout(true);
                }
                console.log(response);
            }
        }
    }

    const createSocket = () => {
        const webSocket = new WebSocket('ws://localhost:8080');
        updateWS(webSocket);
        webSocket.onopen = () => {
            console.log('WebSocket Client Connected');
            const gameID = roomID.split('G')[1];
            webSocket.send(gameID);
        };
        webSocket.onmessage = socketOnMessage;
        webSocket.onclose = () => {
            console.log('WebSocket Client Disconnected');
        };
    }

    const newGame = async () => {
        const respose = await fetch('http://localhost:4000/new-game/D', {
            method: 'Post',
            headers: {
                'Authorization': token
            }
        })
        const temp = await respose.json();
        setData(temp);
        setRoomID(temp.roomID);
    }

    const startGame = async () => {
        const response = await fetch('http://localhost:4000/start-game', {
            method: 'Post',
            headers: {
                'Authorization': token
            },
            body: JSON.stringify({ roomID: roomID })
        });
        const temp = await response.json();
        setData(temp);
    }

    const handleBeforeUnload = (event) => {
        const confirmationMessage = 'Are you sure you want to leave? You will lose the game.';
        event.returnValue = confirmationMessage;
        return confirmationMessage;
    };

    // create socket
    useEffect(() => {
        if (roomID && !data.message) {
            startGame();
        }
        if (data.message) {
            createSocket();
        }
        return () => {
            if (WS)
                WS.close();
        }
    }, [data, roomID]);


    // update history
    useEffect(() => {
        if (flag) {
            pushOnHistory({ word: word, template: template })
            resetRow();
            toggleFlag();
        }
    }, [flag]);

    const sendMessage = (message) => {
        WS.send(message);
    }

    return (
        <>
            <h1> Welcome to wordle </h1>
            <h2> Room ID: {roomID} </h2>
            {waiting ? (timeout ? <h2> Time out! </h2> : <h2> Waiting for opponent to join... </h2>)
                : <>
                    <h3> Opponent's Template : {opponentTemplate} </h3>
                    <table>
                        <thead>
                            <tr>
                                <th>Guess</th>
                                <th>Template</th>
                            </tr>
                        </thead>
                        <tbody>
                            {history.map((item, idx) => {
                                return (
                                    <tr key={idx}>
                                        <td>{item.word}</td>
                                        <td>{item.template}</td>
                                    </tr>
                                )
                            })}
                        </tbody>
                    </table>
                    <input type="text" value={word} placeholder='Enter a word' onChange={updateWord} disabled={finsihed} />
                    <button onClick={() => { sendMessage(word); }} disabled={finsihed} >Submit</button>
                    {finsihed && (won ? <h2> You won! </h2> : <h2> You lost! </h2>)}
                </>
            }

        </>
    )
}


export default DuoGamePage;
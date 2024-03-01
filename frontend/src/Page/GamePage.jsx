import React from 'react'
import { useState, useEffect } from 'react';

export const GamePage = () => {
    const [WS, setWS] = useState(null);
    const [data, setData] = useState({});
    const [word, setWord] = useState('');
    const [template, setTemplate] = useState('');
    const [history, setHistory] = useState([]);
    const [flag, setFlag] = useState(false);
    const [finsihed, setFinished] = useState(false);
    const [won, setWon] = useState(false);
    const [roomID, setRoomID] = useState('');

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

    const resetAll = () => {
        setWord('');
        setTemplate('');
        setHistory([]);
        setFlag(false);
        setFinished(false);
        setWon(false);
        setData({});
    }

    const token = localStorage.getItem('token');

    const socketOnMessage = (message) => {
        const response = message.data;
        if (response.startsWith('Result: ')) {
            updateTemplate(response.split(' ')[1]);
            toggleFlag();
        } else {
            if (response.includes('win')) {
                finishGame(true);
            } else if (response.includes('lose')) {
                finishGame(false);
            } else {
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
        const respose = await fetch('http://localhost:4000/new-game', {
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
        console.log("hello from start game");
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

    const resetGame = async () => {
        resetAll();
        newGame();
    }

    const handleBeforeUnload = (event) => {
        const confirmationMessage = 'Are you sure you want to leave? You will lose the game.';
        event.returnValue = confirmationMessage;
        return confirmationMessage;
    };


    // create new game
    useEffect(() => {
        newGame();
        window.addEventListener('beforeunload', handleBeforeUnload);
        return () => {
            window.removeEventListener('beforeunload', handleBeforeUnload);
        };
    }, []);

    // create socket
    useEffect(() => {
        console.log("data changed : ", data);
        if (data.roomID) {
            startGame();
        }
        if (data.message) {
            createSocket();
        }
        return () => {
            if (WS)
                WS.close();
        }
    }, [data]);


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
            {finsihed && <button onClick={resetGame}>New Game</button>}
        </>
    )
}

export default GamePage;
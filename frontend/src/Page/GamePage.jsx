import React from 'react'
import { useState, useEffect } from 'react';

export const GamePage = () => {
    const [WS, setWS] = useState(null);
    const [data, setData] = useState({});
    const [word, setWord] = useState('');
    const [history, setHistory] = useState([]);

    const token = localStorage.getItem('token');

    const newGame = async () => {
        const respose = await fetch('http://localhost:4000/new-game', {
            method: 'Post',
            headers: {
                'Authorization': token
            }
        })
        const temp = await respose.json();
        setData(temp);
    }

    const startGame = async () => {
        const response = await fetch('http://localhost:4000/start-game', {
            method: 'Post',
            headers: {
                'Authorization': token
            }
        });
        const temp = await response.json();
    }

    const sendMessage = (message) => {
        WS.send(message);
    }
    useEffect(() => {
        newGame();
        startGame();
    }, []);

    useEffect(() => {
        if (!data.gameID) return;
        const webSocket = new WebSocket('ws://localhost:8080');
            setWS(webSocket);
            webSocket.onopen = () => {
                console.log('WebSocket Client Connected');
                console.log(data.gameID);
                webSocket.send(data.gameID);
            };
            webSocket.onmessage = (message) => {
                const response = message.data;
                if (response.startsWith('Result: ') ) {
                    updateHistory( { word: word, template: response.split(' ')[1] } )
                    console.log(history);
                    console.log(response);
                    console.log(word);
                }
            };
            webSocket.onclose = () => {
                console.log('WebSocket Client Disconnected');
            };
        return () => {
            webSocket.close();
        }
    },[data.gameID]);

    const updateWord = (e) => {
        setWord(e.target.value);
    }

    const updateHistory =  (row) => {
        setHistory( (history) => [...history, row]) ;
    }

    useEffect(() => {
        console.log(history);
        console.log(word);
    },[word]);

    useEffect(() => {
        console.log(history);
    },[history]);

    return (
        <>
            <h1> Welcome to wordle </h1>
            <h2> Game ID: {data.gameID} </h2>
            <table>
                <thead>
                    <tr>
                        <th>Guess</th>
                        <th>Template</th>
                    </tr>
                </thead>
                <tbody>
                    {history.map((item,idx) => {
                        return (
                            <tr key={idx}>
                                <td>{item.word}</td>
                                <td>{item.template}</td>
                            </tr>
                        )
                    })}
                </tbody>
            </table>
            <input type="text" value={word} placeholder='Enter a word' onChange={updateWord} />
            <button onClick={() => { sendMessage(word); }}>Submit</button>
        </>
    )
}

export default GamePage;
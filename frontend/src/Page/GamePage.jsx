import React from 'react'
import { useState, useEffect } from 'react';

export const GamePage = () => {
    const [data, setData] = useState({});
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
    useEffect(() => {
        newGame();
    }, []);
    return (
        <>
            <h1> Welcome to wordle </h1>
            <h2> Game ID: {data.gameID} </h2>
        </>
    )
}

export default GamePage;
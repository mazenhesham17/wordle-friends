import React from 'react'
import { useState, useEffect } from 'react';

export const GamePage = () => {
    const [data, setData] = useState({});
    const token = localStorage.getItem('token');
    useEffect(() => {
        fetch('http://localhost:4000/new-game', {
            method: 'Post',
            headers: {
                'Authorization': token
            }
        })
            .then(response => response.json())
            .then(body => {
                setData(body);
            })
            .catch(err => console.error(err));
    }, [token]);
  return (
    <>
    <h1> Welcome to wordle </h1>
    <h2> Game ID: {data.gameID} </h2>
    </>
  )
}

export default GamePage;
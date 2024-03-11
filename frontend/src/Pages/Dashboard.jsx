import React, { useEffect, useState } from 'react'

export const Dashboard = () => {
    const [data, setData] = useState({});
    const token = localStorage.getItem('token');
    const fetchData = async () => {
        const response = await fetch('http://localhost:4000/dashboard', {
            method: 'GET',
            headers: {
                'Authorization': token
            }
        });
        const temp = await response.json();
        setData(temp);
    }
    useEffect(() => {
        fetchData();
    }, []);
    return (
        <>
            <h1>Dashboard</h1>
            <h2>Number of players : {data.totalPlayers}</h2>
            <h2>Number of games winned : {data.totalWins}</h2>
            <h2>Number of games : {data.totalGames}</h2>
        </>

    )
}

export default Dashboard;
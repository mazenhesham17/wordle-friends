import React, { useEffect, useState } from 'react'
import { Link } from 'react-router-dom';

export const Profile = () => {
    const [data, setData] = useState({});
    const token = localStorage.getItem('token');
    const fetchData = async () => {
        const response = await fetch('http://localhost:4000/profile', {
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
        <div>
            <h1>Profile</h1>
            <ul>
                <li>Role: {data.userType}</li>
                <li>Username: {data.username}</li>
                {data.userType === "player" &&
                    <>
                        <li>First Name: {data.firstName}</li>
                        <li>Last Name: {data.lastName}</li>
                    </>
                }
                <li>Email: {data.email}</li>
                {data.userType === "player" &&
                    <>
                        <li>Games Won: {data.wins}</li>
                        <li>Games Played: {data.games}</li>
                    </>
                }
            </ul>
            {data.userType === "player" &&
                <>
                    <Link to="/game">New Game</Link>
                    <br />
                </>
            }
            {data.userType === "admin" &&
                <>
                    <Link to="/dashboard">dashboard</Link>
                    <br />
                </>
            }
            <button onClick={() => {
                localStorage.removeItem('token');
                window.location.href = '/';
            }
            }>Logout</button>
        </div>
    )
}

export default Profile;
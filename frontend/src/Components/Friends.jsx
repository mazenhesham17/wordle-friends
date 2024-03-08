import React, { useEffect, useState } from 'react'

export const Friends = () => {
    const token = localStorage.getItem('token');
    const [friends, setFriends] = useState([]);
    const [error, setError] = useState('');

    const fetchFriends = async () => {
        const response = await fetch('http://localhost:4000/friends', {
            method: 'GET',
            headers: {
                'Authorization': token
            }
        });
        const data = await response.json();
        if (data.error) {
            setError(data.error);
            return;
        }
        setFriends(data.players);
    }

    useEffect(() => {
        fetchFriends();
    }, []);
    return (
        <>
            {error ? <div>{error}</div> :
                <div>
                    <h1>Friends</h1>
                    <ul style={{ display: "flex", flexDirection: "column", width: "200px" }}>
                        {
                            friends.map((friend, index) => {
                                return (
                                    <li key={index} style={{ display: "flex" }}>
                                        <h1>{friend.name[0]}</h1>
                                        <h2>{friend.name}</h2>
                                        <h3>{friend.playerID}</h3>
                                        <br />
                                    </li>
                                )
                            })
                        }
                    </ul>
                </div>
            }
        </>
    )
}

export default Friends;
import React, { useState, useEffect } from 'react'

export const FilteredList = (props) => {
    const token = localStorage.getItem('token');
    const [players, setPlayers] = useState([]);
    const [error, setError] = useState('');

    const fetchPlayers = async () => {
        const response = await fetch(`http://localhost:4000/search/${props.query}`, {
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
        setPlayers(data.players);
    }

    const toogleFriend = (playerID) => {
        setPlayers(prevPlayers => {
            return prevPlayers.map(player => {
                if (player.playerID === playerID) {
                    console.log(playerID);
                    return { ...player, isFriend: !player.isFriend };
                }
                return player;
            });
        });
    }

    const addFriend = async (playerID) => {
        const response = await fetch(`http://localhost:4000/add-friend/${playerID}`, {
            method: 'POST',
            headers: {
                'Authorization': token
            },
        });
        const data = await response.json();
        if (data.error) {
            setError(data.error);
            return;
        }
        if (data.message === "success") {
            toogleFriend(playerID);
        }
    }

    useEffect(() => {
        if (props.query)
            fetchPlayers();
        else
            setPlayers([]);
    }, [props.query]);

    return (
        <>
            {error ? <div>{error}</div> : null}
            <ul style={{ display: "flex", flexDirection: "column", width: "200px" }}>
                {
                    players.map((player, index) => {
                        return (
                            <li key={index} style={{ display: "flex" }}>
                                <h1>{player.name[0]}</h1>
                                <h2>{player.name}</h2>
                                <h3>{player.playerID}</h3>
                                {player.isFriend ? <button onClick={() => addFriend(player.playerID)}>Add Friend</button> : null}
                                <br />
                            </li>
                        )
                    })
                }
            </ul>
        </>

    )
}

export default FilteredList;
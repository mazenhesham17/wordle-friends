import React, { useState, useEffect, useContext } from 'react'
import Card from './Card';
import { useSelector } from 'react-redux';
import { FunctionContext } from '../../App';
import { getRandomColor } from '../../Util/random';

export const FilteredList = () => {
    const token = localStorage.getItem('token');
    const showErrorMessage = useContext(FunctionContext);
    const query = useSelector(state => state.search.query);
    const [players, setPlayers] = useState([]);

    const fetchPlayers = async () => {
        try {
            const response = await fetch(`http://localhost:4000/api/search/${query}`, {
                method: 'GET',
                headers: {
                    'Authorization': token
                }
            });
            const responseJSON = await response.json();
            if (responseJSON.error) {
                showErrorMessage(responseJSON.error);
            } else {
                setPlayers(responseJSON.players);
            }
        } catch ({ name, message }) {
            showErrorMessage(message);
        }
    }



    useEffect(() => {
        if (query === '')
            setPlayers([])
        else
            fetchPlayers();
    }, [query]);


    return (
        <>
            <div style={{ display: "flex", flexDirection: "column", width: "max-content" }}>
                {
                    players.length ?
                        players.map((player, index) => {
                            return (
                                <Card key={index}
                                    color={getRandomColor()} playerID={player.playerID}
                                    firstName={player.firstName} lastName={player.lastName}
                                    username={player.username} isFriend={player.isFriend}
                                />
                            )
                        }) : query.length ? <Card isEmpty={true} /> : null
                }
            </div>
        </>
    )
}

export default FilteredList;
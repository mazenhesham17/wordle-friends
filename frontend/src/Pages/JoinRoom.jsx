import React, { useState, useEffect } from 'react'
import { useNavigate } from 'react-router-dom';

export const JoinRoom = () => {
    const navigate = useNavigate();
    const token = localStorage.getItem('token');
    const [roomID, setRoomID] = useState('');
    const [error, setError] = useState('');
    const [correct, setCorrect] = useState(false);

    const updateRoomID = (e) => {
        setRoomID(e.target.value);
    }

    const checkRoomID = async () => {
        const response = await fetch(`http://localhost:4000/check-room/${roomID}`, {
            method: 'GET',
            headers: {
                'Authorization': token
            },
        });
        const temp = await response.json();
        if (temp.error) {
            setError(temp.error);
        } else {
            setCorrect(true);
        }
    }

    useEffect(() => {
        if (correct) {
            navigate(`/duo-game/${roomID}`);
        }
    }, [correct]);

    return (
        <>
            <div>JoinRoom</div>
            <input type="text" value={roomID} onChange={updateRoomID} />
            {error && <div>{error}</div>}
            <button onClick={checkRoomID}>Join</button>
        </>
    )
}

export default JoinRoom;
import React, { useContext, useEffect, useState } from 'react'
import { FunctionContext } from '../../App';
import { useNavigate } from 'react-router-dom';
import styles from './Styles/joinbar.module.css';

export const JoinBar = () => {
    const navigate = useNavigate();
    const token = localStorage.getItem('token');
    const showErrorMessage = useContext(FunctionContext);
    const [roomID, setRoomID] = useState('');
    const [correct, setCorrect] = useState(false);

    const updateRoomID = (e) => {
        setRoomID(e.target.value);
    }

    const checkRoomID = async () => {
        try {
            const response = await fetch(`http://localhost:4000/api/game/check-room/${roomID}`, {
                method: 'GET',
                headers: {
                    'Authorization': token
                },
            });
            const responseJSON = await response.json();
            if (responseJSON.error) {
                showErrorMessage(responseJSON.error);
            } else {
                setCorrect(true);
            }
        } catch ({ name, message }) {
            showErrorMessage(message);
        }


    }

    useEffect(() => {
        if (correct) {
            navigate(`/game/${roomID}`);
        }
    }, [correct]);

    return (
        <div className={styles.container} >
            <input type="text" value={roomID} onChange={updateRoomID} placeholder='Room ID' />
            <div className={styles.right_align} >
                <button onClick={checkRoomID}>Join</button>

            </div>
        </div>
    )
}

export default JoinBar;
import React, { useContext, useState } from 'react'
import { useNavigate } from 'react-router-dom';
import { FunctionContext } from '../../App';
import { generateUrl } from '../../Util/urls';
import styles from './Styles/joinbar.module.css';

export const JoinBar = () => {
    const token = localStorage.getItem('token');
    const navigate = useNavigate();
    const showErrorMessage = useContext(FunctionContext);
    const [roomID, setRoomID] = useState('');

    const updateRoomID = (e) => {
        setRoomID(e.target.value);
    }

    const checkRoomID = async () => {
        try {
            const url = generateUrl('game', 'check-room', roomID);
            const response = await fetch(url, {
                method: 'GET',
                headers: {
                    'Authorization': token
                },
            });
            const responseJSON = await response.json();
            if (responseJSON.error) {
                showErrorMessage(responseJSON.error);
            } else {
                navigate(`/game/${roomID}`);
            }
        } catch ({ name, message }) {
            showErrorMessage(message);
        }


    }

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
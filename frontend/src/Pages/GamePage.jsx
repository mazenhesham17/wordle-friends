import React, { useEffect, useContext, useState } from 'react'
import { useDispatch, useSelector } from 'react-redux';
import { chageTitle, changePage } from '../State/pageSlice';
import { useNavigate } from 'react-router-dom';
import styles from './Styles/gamepage.module.css';
import { FunctionContext } from '../App';
import JoinBar from '../Components/Game/JoinBar';

export const GamePage = () => {
    const token = localStorage.getItem('token');
    const dispatch = useDispatch();
    const navigate = useNavigate();
    const showErrorMessage = useContext(FunctionContext);
    const title = useSelector(state => state.page.title);
    const [roomID, setRoomID] = useState('');

    useEffect(() => {
        dispatch(changePage('game'));
        dispatch(chageTitle('Game'));
    }, []);

    const newGame = async (type) => {
        try {
            const respose = await fetch(`http://localhost:4000/api/game/new/${type}`, {
                method: 'Post',
                headers: {
                    'Authorization': token
                }
            })
            const responseJSON = await respose.json();
            if (responseJSON.error) {
                showErrorMessage(responseJSON.error);
                return;
            }
            setRoomID(responseJSON.roomID);
        }
        catch ({ name, message }) {
            showErrorMessage(message);
        }
    }

    useEffect(() => {
        if (roomID) {
            navigate(`/game/${roomID}`);
        }
    }, [roomID]);


    return (
        <div className={styles.main_container} >
            {title === 'Join Room' ? <JoinBar /> : <div className={styles.container} >
                <button onClick={
                    async () => {
                        await newGame('D');
                    }
                } >Create room</button>
                <button onClick={
                    () => { dispatch(chageTitle('Join Room')) }
                } >Join room</button>
                <button onClick={
                    async () => {
                        await newGame('S');
                    }
                } >Single game</button>
            </div>}

        </div>
    )
}

export default GamePage;
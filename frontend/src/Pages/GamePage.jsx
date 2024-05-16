import React, { useEffect, useContext } from 'react'
import { useNavigate } from 'react-router-dom';
import { useDispatch, useSelector } from 'react-redux';
import { chageTitle, changePage } from '../State/pageSlice';
import { FunctionContext } from '../App';
import JoinBar from '../Components/Game/JoinBar';
import styles from './Styles/gamepage.module.css';

export const GamePage = () => {
    const token = localStorage.getItem('token');
    const navigate = useNavigate();
    const dispatch = useDispatch();
    const showErrorMessage = useContext(FunctionContext);
    const title = useSelector(state => state.page.title);

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
            navigate(`/game/${responseJSON.roomID}`);
        }
        catch ({ name, message }) {
            showErrorMessage(message);
        }
    }

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
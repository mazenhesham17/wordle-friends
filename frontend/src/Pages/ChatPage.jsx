import React, { useState, useEffect } from 'react'
import Friends from '../Components/Friends';
import Chat from '../Components/Chat';
import { useDispatch } from 'react-redux';
import { changePage, chageTitle } from '../State/pageSlice';

export const ChatPage = (props) => {
    const dispatch = useDispatch();
    useEffect(() => {
        dispatch(changePage('chat'));
        dispatch(chageTitle('My chat'));
    }, [])

    const [playerID, setPlayerID] = useState('');

    const updatePlayerID = (id) => {
        setPlayerID(id);
    }
    return (
        <>
            <div style={{ display: "flex" }}>
                <Friends updateChat={updatePlayerID} />
                <Chat friendID={playerID} />
            </div>
        </>
    )
}

export default ChatPage;
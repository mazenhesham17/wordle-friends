import React, { useState } from 'react'
import Friends from '../Components/Friends';
import Chat from '../Components/Chat';

export const ChatPage = () => {
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
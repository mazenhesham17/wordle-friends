import React from 'react'
import Friends from '../Components/Friends';

export const ChatPage = () => {
    return (
        <>
            <div style={{ display: "flex" }}>
                <Friends />
                <h1>Room</h1>
            </div>
        </>
    )
}

export default ChatPage;
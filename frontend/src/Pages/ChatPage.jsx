import React, { useEffect } from 'react';
import Friends from '../Components/Chat/FriendsList';
import Chat from '../Components/Chat/Chat';
import { useDispatch } from 'react-redux';
import { changePage, chageTitle } from '../State/pageSlice';

export const ChatPage = () => {
    const dispatch = useDispatch();
    useEffect(() => {
        dispatch(changePage('chat'));
        dispatch(chageTitle('My chat'));
    }, [])

    return (
        <div style={{ display: "flex" }}>
            <Friends />
            <Chat />
        </div>
    )
}

export default ChatPage;
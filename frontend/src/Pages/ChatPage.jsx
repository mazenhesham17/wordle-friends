import React, { useEffect } from 'react';
import { useDispatch } from 'react-redux';
import { changePage, chageTitle } from '../State/pageSlice';
import Friends from '../Components/Chat/FriendsList';
import Chat from '../Components/Chat/Chat';
import styles from './Styles/chatpage.module.css';

export const ChatPage = () => {
    const dispatch = useDispatch();

    useEffect(() => {
        dispatch(changePage('chat'));
        dispatch(chageTitle('My chat'));
    }, [])

    return (
        <div className={styles.row}>
            <Friends />
            <Chat />
        </div>
    )
}

export default ChatPage;
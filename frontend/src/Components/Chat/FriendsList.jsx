import React, { useEffect, useState, useContext } from 'react'
import { FunctionContext } from '../../App';
import { useSelector, useDispatch } from 'react-redux';
import Card from './Card';
import styles from './Styles/list.module.css';
import { getRandomColor } from '../../Util/random';
import { changeMessage } from '../../State/chatSlice';

export const Friends = () => {
    const token = localStorage.getItem('token');
    const showErrorMessage = useContext(FunctionContext);
    const dispatch = useDispatch();
    const [friends, setFriends] = useState([]);
    const [colors, setColors] = useState([]);
    const newMessage = useSelector(state => state.chat.newMessage);
    const activeChat = useSelector(state => state.chat.activeChat);
    const [flag, setFlag] = useState(false);
    const [readStatus, setReadStatus] = useState([]);

    const fetchFriends = async () => {
        try {
            const response = await fetch('http://localhost:4000/api/chat/friends', {
                method: 'Get',
                headers: {
                    'Authorization': token
                },
            });
            const responseJSON = await response.json();
            if (responseJSON.error) {
                showErrorMessage(responseJSON.error);
                return;
            }
            setFriends(responseJSON.friends);
            setReadStatus(responseJSON.friends.map(friend => friend.read));
            setColors(Array.from({ length: responseJSON.friends.length }, () => getRandomColor()))
        } catch ({ name, message }) {
            showErrorMessage(message);
        }
    }

    useEffect(() => {
        fetchFriends();
    }, []);

    const moveFriendToTop = (friendID) => {
        const friendIndex = friends.findIndex(friend => friend.friendID == friendID);
        if (friendIndex > 0) {
            const updatedFriends = [friends[friendIndex], ...friends.slice(0, friendIndex), ...friends.slice(friendIndex + 1)];
            const updatedReadStatus = [readStatus[friendIndex], ...readStatus.slice(0, friendIndex), ...readStatus.slice(friendIndex + 1)];
            const updatedColors = [colors[friendIndex], ...colors.slice(0, friendIndex), ...colors.slice(friendIndex + 1)];
            setFriends(updatedFriends);
            setReadStatus(updatedReadStatus);
            setColors(updatedColors);
        }
    };

    const updateReadStatus = (friendID, status) => {
        const friendIndex = friends.findIndex(friend => friend.friendID == friendID);
        if (friendIndex !== -1) {
            const updatedReadStatus = [...readStatus];
            updatedReadStatus[friendIndex] = status;
            setReadStatus(updatedReadStatus);
        }
    };

    useEffect(() => {
        if (newMessage != null) {
            moveFriendToTop(newMessage);
            setFlag(true);

        }

    }, [newMessage]);

    useEffect(() => {
        if (!flag) return;
        if (activeChat?.friendID != newMessage) {
            updateReadStatus(newMessage, 0);
        }
        dispatch(changeMessage(null));
        setFlag(false);
    }, [flag]);

    useEffect(() => {
        if (activeChat != null) {
            updateReadStatus(activeChat.friendID, 1);
        }
    }, [activeChat]);

    return (
        <div className={styles.container} >
            <h1 className={styles.title} >Chats</h1>
            {friends.length === 0 ? <p className={styles.empty}> Add friend to chat with </p> : null}
            <div className={styles.friends_container} >
                {
                    friends.map((friend, index) => {
                        return (
                            <Card key={index}
                                friendID={friend.friendID}
                                firstName={friend.firstName} lastName={friend.lastName}
                                read={readStatus[index]} color={colors[index]} />
                        )
                    })
                }
            </div>
        </div>
    )
}

export default Friends;
import React, { useEffect, useState, useContext } from 'react'
import { useSelector, useDispatch } from 'react-redux';
import { changeMessage } from '../../State/chatSlice';
import { FunctionContext } from '../../App';
import { getRandomColor } from '../../Util/random';
import Card from './Card';
import styles from './Styles/list.module.css';

export const Friends = () => {
    const token = localStorage.getItem('token');
    const dispatch = useDispatch();
    const showErrorMessage = useContext(FunctionContext);
    const newMessage = useSelector(state => state.chat.newMessage);
    const activeChat = useSelector(state => state.chat.activeChat);

    const [friends, setFriends] = useState([]);
    const [flag, setFlag] = useState(false);

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
            setFriends(responseJSON.friends.map((friend) => {
                return { ...friend, color: getRandomColor() };
            }));
        } catch ({ name, message }) {
            showErrorMessage(message);
        }
    }

    const moveFriendToTop = (friendID) => {
        const friendIndex = friends.findIndex(friend => friend.friendID == friendID);
        if (friendIndex <= 0) return;

        const updatedFriends = [friends[friendIndex], ...friends.slice(0, friendIndex), ...friends.slice(friendIndex + 1)];
        setFriends(updatedFriends);
    };

    const updateReadStatus = (friendID, status) => {
        const friendIndex = friends.findIndex(friend => friend.friendID == friendID);
        if (friendIndex === -1) return;

        const updatedFriends = [...friends];
        updatedFriends[friendIndex].read = status;
        setFriends(updatedFriends);
    };

    useEffect(() => {
        fetchFriends();
    }, []);

    useEffect(() => {
        if (newMessage == null) return;

        moveFriendToTop(newMessage);
        setFlag(true);
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
        if (activeChat == null) return;

        updateReadStatus(activeChat.friendID, 1);
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
                                read={friend.read} color={friend.color} />
                        )
                    })
                }
            </div>
        </div>
    )
}

export default Friends;
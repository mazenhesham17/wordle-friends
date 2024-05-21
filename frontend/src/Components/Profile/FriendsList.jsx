import React, { useContext, useEffect, useState } from 'react'
import { Avatar } from 'primereact/avatar';
import { AvatarGroup } from 'primereact/avatargroup';
import { FunctionContext } from '../../App';
import { getRandomColor } from '../../Util/random';
import { generateUrl } from '../../Util/urls';
import styles from './Styles/friendslist.module.css';


export const FriendsList = () => {
    const token = localStorage.getItem('token');
    const showErrorMessage = useContext(FunctionContext);
    const [friends, setFriends] = useState([]);

    const fetchData = async () => {
        try {
            const url = generateUrl('profile', 'friends');
            const response = await fetch(url, {
                method: 'GET',
                headers: {
                    'Authorization': token
                }
            });
            const responseJSON = await response.json();
            if (responseJSON.error) {
                showErrorMessage(responseJSON.error);
            } else {
                setFriends(responseJSON.friends);
            }
        } catch ({ name, message }) {
            showErrorMessage(message);
        }
    }

    useEffect(() => {
        fetchData();
    }, []);

    return (
        <div className={styles.container} >
            <div className={styles.row} >
                <box-icon name='group' size="md" color='#B1B2FF'></box-icon>
                <h1>Friends</h1>
            </div>
            <AvatarGroup className={styles.group} >
                {friends.slice(0, 5).map((friend, index) => (
                    <Avatar
                        key={index}
                        label={friend.label}
                        size="xlarge"
                        shape="circle"
                        className={styles.avatar}
                        style={{ backgroundColor: getRandomColor() }}
                    />
                ))}
                {friends.length > 5 && (
                    <Avatar
                        key="more"
                        label="+"
                        size="xlarge"
                        shape="circle"
                        className={styles.avatar}
                        style={{ backgroundColor: getRandomColor() }}
                    />
                )}
            </AvatarGroup>
        </div>
    )
}

export default FriendsList;
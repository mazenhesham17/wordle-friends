import React, { useEffect } from 'react'
import { useDispatch } from 'react-redux';
import { chageTitle, changePage } from '../State/pageSlice';
import PersonalInfo from '../Components/Profile/PersonalInfo';
import GameChart from '../Components/Profile/GameChart';
import FriendsList from '../Components/Profile/FriendsList';
import styles from './Styles/layout.module.css';

export const Profile = () => {
    const dispatch = useDispatch();
    useEffect(() => {
        dispatch(changePage('profile'));
        dispatch(chageTitle('My profile'));
    }, [])
    return (
        <div className={styles.row} >
            <PersonalInfo />
            <div className={styles.column}>
                <GameChart />
                <FriendsList />
            </div>
        </div>
    )
}

export default Profile;
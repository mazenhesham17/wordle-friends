import React from 'react'
import styles from './Styles/sidebar.module.css';
import SideBarIcon from './SideBarIcon';
import { useSelector } from 'react-redux';
import NotificationIcon from './NotificationIcon';

export const Sidebar = () => {
    const userType = useSelector(state => state.auth.role);
    if (!userType || userType === 'admin')
        return null;
    return (
        <aside className={styles.list} >
            <div className={styles.title} >
                <h1>Wordle</h1>
                <h1>Friends</h1>
            </div>
            <SideBarIcon name='user' title='profile' />
            <SideBarIcon name='joystick' title='game' />
            <NotificationIcon name='conversation' title='chat' />
            <SideBarIcon name='search' title='search' />
        </aside>
    )
}

export default Sidebar;
import React from 'react'
import { useDispatch, useSelector } from 'react-redux';
import { flipSidebar } from '../../State/pageSlice';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faXmark } from '@fortawesome/free-solid-svg-icons';
import NotificationIcon from './NotificationIcon';
import SideBarIcon from './SideBarIcon';
import styles from './Styles/sidebar.module.css';

export const Sidebar = () => {
    const dispatch = useDispatch();
    const userType = useSelector(state => state.auth.role);
    const sidebar = useSelector(state => state.page.sidebar);
    if (!userType || userType === 'admin')
        return null;
    return (
        <aside className={`${styles.list} ${sidebar ? styles.visible : ''}`} >
            <div className={styles.row} >
                <div className={styles.title} >
                    <h1>Wordle</h1>
                    <h1>Friends</h1>

                </div>
                <button className={styles.button} onClick={() => { dispatch(flipSidebar()) }} >
                    <FontAwesomeIcon icon={faXmark} size="2x" color="#B1B2FF" />
                </button>
            </div>

            <SideBarIcon name='user' title='profile' />
            <SideBarIcon name='joystick' title='game' />
            <NotificationIcon name='conversation' title='chat' />
            <SideBarIcon name='search' title='search' />
        </aside>
    )
}

export default Sidebar;
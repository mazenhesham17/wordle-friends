import React from 'react'
import { useSelector } from 'react-redux';
import { Link } from 'react-router-dom';
import styles from './Styles/sidebar.module.css';

export const SideBarIcon = (props) => {
    const pageName = useSelector(state => state.page.name);
    return (
        <Link to={`/${props.title}`} >
            <div className={`${styles.container} ${styles.item} ${pageName === props.title ? styles.active : ''}`} >
                <box-icon name={props.name} size="md" color='#B1B2FF'></box-icon>
                <h2>{props.title}</h2>
            </div>
        </Link>
    )
}

export default SideBarIcon;

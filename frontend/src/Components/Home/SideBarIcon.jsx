import React from 'react'
import styles from './Styles/sidebar.module.css';
import { useSelector } from 'react-redux';
import { Link } from 'react-router-dom';

export const SideBarIcon = (props) => {
    const pageName = useSelector(state => state.page.name);
    return (
        <div className={`${styles.container} ${pageName === props.title ? styles.active : ''} `} >
            <Link to={`/${props.title}`} >
                <box-icon name={props.name} size="md" color='#B1B2FF'></box-icon>
            </Link>
            <h2>{props.title}</h2>
        </div>
    )
}

export default SideBarIcon;

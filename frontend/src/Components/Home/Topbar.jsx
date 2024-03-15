import React from 'react'
import styles from './Styles/topbar.module.css';
import InformationCard from './InformationCard';
import { useSelector } from 'react-redux';
import Searchbar from '../Search/Searchbar';

export const Topbar = () => {
    const userType = useSelector(state => state.auth.role);
    const title = useSelector(state => state.page.title);
    const pageName = useSelector(state => state.page.name);
    if (!userType)
        return null;
    return (
        <div className={styles.container}>
            {pageName === 'search' ? <Searchbar /> : <h1>{title}</h1>}
            <InformationCard />
        </div>
    )
}

export default Topbar;

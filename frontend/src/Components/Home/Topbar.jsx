import React from 'react'
import { useDispatch, useSelector } from 'react-redux';
import { flipSidebar } from '../../State/pageSlice';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faBars } from '@fortawesome/free-solid-svg-icons';
import InformationCard from './InformationCard';
import Searchbar from '../Search/Searchbar';
import styles from './Styles/topbar.module.css';


export const Topbar = () => {
    const dispatch = useDispatch();
    const userType = useSelector(state => state.auth.role);
    const title = useSelector(state => state.page.title);
    const pageName = useSelector(state => state.page.name);

    if (!userType)
        return null;
    return (
        <div className={styles.container}>
            <div className={styles.row} >
                <button className={styles.button} onClick={() => { dispatch(flipSidebar()) }} >
                    <FontAwesomeIcon icon={faBars} size="2x" color="#B1B2FF" />
                </button>
                {pageName === 'search' ? <Searchbar /> : <h1 className={styles.title} >{title}</h1>}
            </div>
            <InformationCard />
        </div>
    )
}

export default Topbar;

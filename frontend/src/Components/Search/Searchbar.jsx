import React from 'react';
import { useSelector, useDispatch } from 'react-redux';
import { changeQuery } from '../../State/searchSlice';
import styles from './Styles/searchbar.module.css';

const Searchbar = () => {
    const query = useSelector(state => state.search.query);
    const dispatch = useDispatch();
    const handleInputChange = (e) => {
        dispatch(changeQuery(e.target.value))
    };

    return (
        <div className={styles.container}>
            <input type="text" value={query} placeholder='username' onChange={handleInputChange} />
            <div className={styles.searchIcon}>
                <box-icon name='search' color='#B1B2FF' size='md' ></box-icon>
            </div>
        </div>
    );
};

export default Searchbar;
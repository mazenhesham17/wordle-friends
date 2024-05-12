import React, { useEffect } from 'react'
import { useDispatch } from 'react-redux';
import { changePage } from '../State/pageSlice';
import { changeQuery } from '../State/searchSlice';
import FilteredList from '../Components/Search/FilteredList';

export const SearchPage = () => {
    const dispatch = useDispatch();
    useEffect(() => {
        dispatch(changePage('search'));
        return () => {
            dispatch(changeQuery(''))
        }
    }, [])
    return (
        <FilteredList />
    )
}

export default SearchPage;

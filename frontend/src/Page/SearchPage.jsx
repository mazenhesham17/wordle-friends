import React, { useState } from 'react'
import FilteredList from '../Components/FilteredList';

export const SearchPage = () => {
    const [query, setQuery] = useState('');

    const updateQuery = (e) => {
        setQuery(e.target.value);
    }

    return (
        <>
            <div>SearchPage</div>
            <input type="text" value={query} onChange={updateQuery} placeholder='search by username' />
            <FilteredList query={query} />
        </>
    )
}

export default SearchPage;

import { createSlice } from '@reduxjs/toolkit';

const searchSlice = createSlice({
    name: 'search',
    initialState: {
        query: '',
    },
    reducers: {
        changeQuery: (state, action) => {
            state.query = action.payload;
        },
    },
});

export const { changeQuery } = searchSlice.actions;

export default searchSlice.reducer;
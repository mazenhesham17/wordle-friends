import { createSlice } from '@reduxjs/toolkit';


const gameSlice = createSlice({
    name: 'game',
    initialState: {
        inputValue: '',
        clear: false,
    },
    reducers: {
        changeInput: (state, action) => {
            state.inputValue = action.payload;
        },
        toggleClear: (state) => {
            state.clear = !state.clear;
        }
    },
});

export const { changeInput, toggleClear } = gameSlice.actions;

export default gameSlice.reducer;
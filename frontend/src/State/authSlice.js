import { createSlice } from '@reduxjs/toolkit';

const authSlice = createSlice({
    name: 'auth',
    initialState: {
        role: localStorage.getItem('userType') || null,
    },
    reducers: {
        reduxLogin: (state, action) => {
            state.role = action.payload;
        },
        reduxLogout: (state) => {
            state.role = null;
        },
    },
});

export const { reduxLogin, reduxLogout } = authSlice.actions;

export default authSlice.reducer;
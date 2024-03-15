import { createSlice } from "@reduxjs/toolkit";

export const pageSlice = createSlice({
    name: 'page',
    initialState: {
        name: 'profile',
        title: 'My profile',
    },
    reducers: {
        changePage: (state, action) => {
            state.name = action.payload
        },
        chageTitle: (state, action) => {
            state.title = action.payload
        },
    }
})

export const { changePage , chageTitle , changeRole } = pageSlice.actions

export default pageSlice.reducer
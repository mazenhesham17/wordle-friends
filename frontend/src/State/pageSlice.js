import { createSlice } from "@reduxjs/toolkit";

export const pageSlice = createSlice({
    name: 'page',
    initialState: {
        name: 'profile',
        title: 'My profile',
        sidebar: false,
    },
    reducers: {
        changePage: (state, action) => {
            state.name = action.payload
            state.sidebar = false
        },
        chageTitle: (state, action) => {
            state.title = action.payload
        },
        flipSidebar: (state) => {
            state.sidebar = !state.sidebar
        }
    }
})

export const { changePage, chageTitle, changeRole, flipSidebar } = pageSlice.actions

export default pageSlice.reducer
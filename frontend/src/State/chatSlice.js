import { createSlice } from '@reduxjs/toolkit';

const chatSlice = createSlice({
    name: 'chat',
    initialState: {
        activeChat: null,
        newMessage: null,
        unseenChats: [],
    },
    reducers: {
        changeChat: (state, action) => {
            state.activeChat = action.payload;
        },
        changeMessage: (state, action) => {
            state.newMessage = action.payload;
        },
        removeChat: (state) => {
            state.activeChat = '';
        },
        addUnseenChat: (state, action) => {
            if (action.payload === state.activeChat)
                return;
            if (state.unseenChats.includes(action.payload))
                return;
            state.unseenChats = [...state.unseenChats, action.payload];
        },
        clear: (state) => {
            state.unseenChats = [];
        },
    },
});

export const { changeChat, changeLabel, removeChat, addUnseenChat, clear, changeMessage } = chatSlice.actions;

export default chatSlice.reducer;
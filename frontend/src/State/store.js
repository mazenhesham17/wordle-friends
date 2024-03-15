import { configureStore } from '@reduxjs/toolkit'
import pageReducer from './pageSlice'
import searchReducer from './searchSlice'
import authReducer from './authSlice'

export default configureStore({
  reducer: {
    page: pageReducer,
    search: searchReducer,
    auth: authReducer,
  },
})
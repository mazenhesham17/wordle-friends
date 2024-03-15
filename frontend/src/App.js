import './App.css';
import React, { createContext, useRef } from 'react';
import { Route, Routes } from 'react-router-dom';
import HomePage from './Pages/HomePage';
import Profile from './Pages/ProfilePage';
import Dashboard from './Pages/Dashboard';
import ChatPage from './Pages/ChatPage';
import SearchPage from './Pages/SearchPage';
import LoginForm from './Components/Registeration/LoginForm';
import RegistrationForm from './Components/Registeration/RegistrationForm';
import Sidebar from './Components/Home/Sidebar';
import Topbar from './Components/Home/Topbar';
import { Toast } from 'primereact/toast';

const FunctionContext = createContext();

function App() {
  const toastRef = useRef(null);

  const showErrorMessage = (message) => {
    toastRef.current.show({ severity: 'error', summary: 'Error', detail: message });
  }

  return (
    <div className='App'>
      <FunctionContext.Provider value={showErrorMessage}>
        <Toast ref={toastRef} />
        <Sidebar />
        <div className='container'>
          <Topbar />
          <Routes >
            <Route path="/" element={<HomePage />} />
            <Route path="/login" element={<LoginForm />} />
            <Route path="/profile" element={<Profile />} />
            <Route path="/register" element={<RegistrationForm />} />
            <Route path="/dashboard" element={<Dashboard />} />
            <Route path="/chat" element={<ChatPage />} />
            <Route path="/search" element={<SearchPage />} />
            <Route element={<h1>not found</h1>}/>
          </Routes>
        </div>
      </FunctionContext.Provider>
    </div>
  );
}

export { FunctionContext };

export default App;

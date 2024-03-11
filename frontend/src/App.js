import './App.css';
import { Route, Routes } from 'react-router-dom';
import HomePage from './Pages/HomePage';
import Profile from './Pages/ProfilePage';
import SingleGamePage from './Pages/SingleGamePage';
import Dashboard from './Pages/Dashboard';
import DuoGamePage from './Pages/DuoGamePage';
import JoinRoom from './Pages/JoinRoom';
import ChatPage from './Pages/ChatPage';
import SearchPage from './Pages/SearchPage';
import LoginForm from './Components/LoginForm';
import RegistrationForm from './Components/RegistrationForm';

function App() {
  return (
    <div className="App">
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route path="/login" element={<LoginForm />} />
        <Route path="/profile" element={<Profile />} />
        <Route path="/register" element={<RegistrationForm />} />
        <Route path="/single-game" element={<SingleGamePage />} />
        <Route path="/duo-game/:urlRoomID?" element={<DuoGamePage />} />
        <Route path="/join-room" element={<JoinRoom />} />
        <Route path="/dashboard" element={<Dashboard />} />
        <Route path="/chat" element={<ChatPage />} />
        <Route path="/search" element={<SearchPage />} />
      </Routes>
    </div>
  );
}

export default App;

import './App.css';
import { Route, Routes } from 'react-router-dom';
import HomePage from './Page/HomePage';
import LoginPage from './Page/LoginPage';
import Profile from './Page/ProfilePage';
import RegisterPage from './Page/RegisterPage';
import SingleGamePage from './Page/SingleGamePage';
import Dashboard from './Page/Dashboard';
import DuoGamePage from './Page/DuoGamePage';
import JoinRoom from './Page/JoinRoom';

function App() {
  return (
    <div className="App">
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route path="/login" element={<LoginPage />} />
        <Route path="/profile" element={<Profile />} />
        <Route path="/register" element={<RegisterPage />} />
        <Route path="/single-game" element={<SingleGamePage />} />
        <Route path="/duo-game/:urlRoomID?" element={<DuoGamePage />} />
        <Route path="/join-room" element={<JoinRoom />} />
        <Route path="/dashboard" element={<Dashboard />} />
      </Routes>
    </div>
  );
}

export default App;

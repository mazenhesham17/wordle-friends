import './App.css';
import { Route , Routes } from 'react-router-dom';
import HomePage from './Page/HomePage';
import LoginPage from './Page/LoginPage';
import Profile from './Page/ProfilePage';
import RegisterPage from './Page/RegisterPage';
import GamePage from './Page/GamePage';
import Dashboard from './Page/Dashboard';

function App() {
  return (
    <div className="App">
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route path="/login" element={<LoginPage />} />
        <Route path="/profile" element={<Profile />} />
        <Route path="/register" element={<RegisterPage/>} />
        <Route path="/game" element={<GamePage />} />
        <Route path="/dashboard" element={<Dashboard/>} />
      </Routes>
    </div>
  );
}

export default App;

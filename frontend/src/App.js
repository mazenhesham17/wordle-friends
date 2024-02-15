import './App.css';
import { HomePage } from './Page/HomePage';
import LoginPage from './Page/LoginPage';
import Profile from './Page/ProfilePage';
import { Route , Routes } from 'react-router-dom';
import RegisterPage from './Page/RegisterPage';
import GamePage from './Page/GamePage';

function App() {
  return (
    <div className="App">
      <Routes>
        <Route path="/" element={<HomePage />} />
        <Route path="/login" element={<LoginPage />} />
        <Route path="/profile" element={<Profile />} />
        <Route path="/register" element={<RegisterPage/>} />
        <Route path="/game" element={<GamePage />} />
      </Routes>
    </div>
  );
}

export default App;

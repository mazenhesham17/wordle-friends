import React, { useEffect, useState } from 'react'
import { Link, useNavigate } from 'react-router-dom'

export const HomePage = () => {
  const [data, setData] = useState({});
  const navigate = useNavigate();
  const token = localStorage.getItem('token');
  const fetchData = async () => {
    const response = await fetch('http://localhost:4000/info', {
      method: 'GET',
      headers: {
        'Authorization': token
      }
    });
    const temp = await response.json();
    setData(temp);
  }

  useEffect(() => {
    if (data?.userType === "admin") {
      navigate('/dashboard');
    }
  }, [data]);

  useEffect(() => {
    if (token) {
      fetchData();
    }
  }, []);

  if (token) {
    return (
      <>
        <div>Welcome to wordle</div>
        <Link to="/single-game">Single Game</Link>
        <br />
        <Link to="/duo-game"> Create Duo Game</Link>
        <br />
        <Link to="/join-room">Join Duo Game</Link>
        <br />
        <Link to="/profile">Profile</Link>
        <br />
        <Link to="/chat">Chat</Link>
        <br />
        <Link to="/search">Search</Link>
        <br />
      </>
    )
  }
  return (
    <>
      <div>Welcome to wordle</div>
      <Link to="/login">Login</Link><br />
      <Link to="/register">Register</Link><br />
    </>
  )
}

export default HomePage;
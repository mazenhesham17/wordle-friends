// Code to redirect user to dashboard or profile page based on user type
import React, { useEffect } from 'react';
import { useNavigate } from 'react-router-dom';


export const HomePage = () => {
  const navigate = useNavigate();
  const userType = localStorage.getItem('userType');

  useEffect(() => {
    if (!userType) {
      navigate('/login');
    }

    if (userType === 'admin') {
      navigate('/dashboard');
    }

    if (userType === 'player') {
      navigate('/profile');
    }
  }, []);

  return null;
}

export default HomePage;
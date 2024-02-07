import React from 'react'
import { Link } from 'react-router-dom'

export const HomePage = () => {
  return (
    <>
    <div>Welcome to wordle</div>
    <Link to="/login">Login</Link>
    <Link to="/register">Register</Link>
    </>
  )
}

export default HomePage;
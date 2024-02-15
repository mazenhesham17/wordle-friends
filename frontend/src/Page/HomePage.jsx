import React from 'react'
import { Link } from 'react-router-dom'

export const HomePage = () => {
  if ( localStorage.getItem('token') ) {
    return (
      <>
      <div>Welcome to wordle</div>
      <Link to="/game">Game</Link>
      </>
    )
  }
  return (
    <>
    <div>Welcome to wordle</div>
    <Link to="/login">Login</Link>
    <Link to="/register">Register</Link>
    <Link to="/game">Game</Link>
    </>
  )
}

export default HomePage;
import React, { useEffect } from 'react'
import { useNavigate } from 'react-router-dom';
import { useState } from 'react';
import { hashPassword } from '../Util/encryption';

export const RegisterPage = () => {
    const navigate = useNavigate();
    const [username, setUsername] = useState("");
    const [firstName, setFirstName] = useState("");
    const [lastName, setLastName] = useState("");
    const [email, setEmail] = useState("");
    const [password, setPassword] = useState("");
    const [error, setError] = useState("");
    const [success, setSuccess] = useState(0);
    const [message, setMessage] = useState("");

    useEffect(() => {
        if (success) {
            setUsername("");
            setFirstName("");
            setLastName("");
            setEmail("");
            setPassword("");
            setMessage("You have successfully registered. Please login.");
            setSuccess(0);
            setTimeout(() => navigate('/login'),1500 );
        }
    }, [success]);

    const submit = async () => {
        const hashedPassword = await hashPassword(password);
        await fetch('http://localhost:4000/register', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ username, firstName, lastName, email, password: hashedPassword }),
        })
            .then(response => response.json())
            .then(body => {
                if (body.error) {
                    setError(body.error);
                } else {
                    setSuccess(1);
                }
            })
            .catch(err => console.error(err));
    }

  return (
    <>
    <h1>Register</h1>
    <form>
        <fieldset>
            <label>
                Username
            </label>
            <input type="text" placeholder="username" value={username} onChange={e => setUsername(e.target.value)} />
        </fieldset>
        <fieldset>
            <label>
                First Name
            </label>
            <input type="text" placeholder="first name" value={firstName} onChange={e => setFirstName(e.target.value)} />
        </fieldset>
        <fieldset>
            <label>
                Last Name
            </label>
            <input type="text" placeholder="last name" value={lastName} onChange={e => setLastName(e.target.value)} />
        </fieldset>
        <fieldset>
            <label>
                Email
            </label>
            <input type="text" placeholder="email" value={email} onChange={e => setEmail(e.target.value)} />
        </fieldset>
        <fieldset>
            <label>
                Password
            </label>
            <input type="password" placeholder="password" value={password} onChange={e => setPassword(e.target.value)} />
        </fieldset>
        {error && <p> {error} </p>}
        {message && <p> {message} </p>}
        <button type="submit" onClick={(e) => { e.preventDefault(); submit(); }}>Register</button>
    </form>
    </>
  )
}

export default RegisterPage;

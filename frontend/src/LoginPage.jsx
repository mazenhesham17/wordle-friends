import React, { useState } from 'react'
import { useNavigate } from 'react-router-dom';


async function hashPassword(plaintextPassword) {
    const encoder = new TextEncoder();
    const data = encoder.encode(plaintextPassword);
    // Use the SubtleCrypto API to hash the password
    const hashBuffer = await crypto.subtle.digest('SHA-256', data);
    // Convert the hash buffer to a hexadecimal string
    const hashArray = Array.from(new Uint8Array(hashBuffer));
    const hashedPassword = hashArray.map(byte => byte.toString(16).padStart(2, '0')).join('');
    return hashedPassword;
}

export const LoginPage = () => {

    const navigate = useNavigate();
    const [identifier, setIdentifier] = useState('');
    const [password, setPassword] = useState('');
    const [error, setError] = useState('');

    const submit = async () => {
        const hashedPassword = await hashPassword(password);
        await fetch('http://localhost:4000/login', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ identifier, password: hashedPassword }),
        })
            .then(response => response.json())
            .then(body => {
                if (body.error) {
                    setError(body.error);
                } else {
                    localStorage.setItem('token', body.token);
                    navigate('/profile');
                }
            })
            .catch(err => console.error(err));
    }

    return (
        <form>
            <fieldset>
                <label>
                    Email or username
                </label>
                <input type="text" placeholder="username" value={identifier} onChange={e => setIdentifier(e.target.value)} />
            </fieldset>
            <fieldset>
                <label>
                    Password
                </label>
                <input type="password" placeholder="password" value={password} onChange={e => setPassword(e.target.value)} />
            </fieldset>
            {error && <p> {error} </p>}
            {localStorage.getItem('token') && <p> You are logged in! </p>}
            <button type="submit" onClick={(e) => { e.preventDefault(); submit(); }}>Login</button>
        </form>
    )
}

export default LoginPage;
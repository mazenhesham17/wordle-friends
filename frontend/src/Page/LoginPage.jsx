import React, { useEffect, useState } from 'react'
import { useNavigate } from 'react-router-dom';
import { hashPassword } from '../Util/encryption';



export const LoginPage = () => {
    const navigate = useNavigate();
    useEffect(() => {
        if (localStorage.getItem('token')) {
            navigate('/profile');
        }
    }, [navigate]);
    const [identifier, setIdentifier] = useState('');
    const [password, setPassword] = useState('');
    const [error, setError] = useState('');

    const submit = async () => {
        const hashedPassword = await hashPassword(password);
        const response = await fetch('http://localhost:4000/login', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ identifier, password: hashedPassword }),
        })
        const temp = await response.json();
        if (temp.error) {
            setError(temp.error);
        } else {
            localStorage.setItem('token', temp.token);
            navigate('/profile');
        }
    }

    return (
        <>
            <h1>Login</h1>
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
        </>
    )
}

export default LoginPage;
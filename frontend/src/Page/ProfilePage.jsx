import React, { useEffect, useState } from 'react'
import { Link } from 'react-router-dom';
import { hashPassword } from '../Util/encryption';

export const Profile = () => {
    const [data, setData] = useState({});
    const [change, setChange] = useState({
        email: false,
        firstName: false,
        lastName: false,
        password: false
    });
    const [update, setUpdate] = useState({
        email: '',
        firstName: '',
        lastName: '',
        password: ''
    });

    const token = localStorage.getItem('token');
    const enableUpdate = (field) => {
        setChange({ ...change, [field]: true });
    }
    const disableUpdate = (field) => {
        setChange({ ...change, [field]: false });
    }
    const updateField = (e, field) => {
        setUpdate({ ...update, [field]: e.target.value });
    }
    const fetchData = async () => {
        const response = await fetch('http://localhost:4000/profile', {
            method: 'GET',
            headers: {
                'Authorization': token
            }
        });
        const temp = await response.json();
        setData(temp);
        setUpdate({ ...update, email: temp.email, firstName: temp.firstName, lastName: temp.lastName });
    }
    const updateRequest = async (field) => {
        // if there is no change in the field, do not send request
        if (data[field] === update[field])
            return disableUpdate(field);
        let hashedPassword;
        if (field === 'password') {
            hashedPassword = await hashPassword(update[field]);
        }
        disableUpdate(field);
        const response = await fetch('http://localhost:4000/profile', {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': token
            },
            body: JSON.stringify({
                [field]: (hashedPassword ? hashedPassword : update[field])
            })
        });
        const temp = await response.json();
        setData(temp);
    }

    useEffect(() => {
        fetchData();
        console.log(change)
        console.log(change.password)
    }, []);

    return (
        <div>
            <h1>Profile</h1>
            <ul>
                {change.password ? <></>
                    : <>
                        <li>Role: {data.userType}</li>
                        <li>Username: {data.username}</li>
                    </>}
                {data.userType === "player" ?
                    <>
                        {change.password ?
                            <>
                                <fieldset>
                                    <legend>Change Password</legend>
                                    <label>New Password</label>
                                    <input type="password" value={update.password} onChange={(e) => { updateField(e, 'password') }} />
                                    <button onClick={() => {
                                        updateRequest('password');
                                    }
                                    }>Save</button>
                                </fieldset>

                            </>
                            : <>
                                {change.firstName ?
                                    <>
                                        <input type="text" value={update.firstName} onChange={(e) => { updateField(e, 'firstName') }} />
                                        <button onClick={() => {
                                            updateRequest('firstName');
                                        }
                                        }>Save</button>
                                    </>
                                    : <li>First Name: {data.firstName}
                                        <button onClick={() => enableUpdate('firstName')}>Edit</button>
                                    </li>}

                                {change.lastName ?
                                    <>
                                        <input type="text" value={update.lastName} onChange={(e) => { updateField(e, 'lastName') }} />
                                        <button onClick={() => {
                                            updateRequest('lastName');
                                        }
                                        }>Save</button>
                                    </>
                                    : <li>Last Name: {data.lastName}
                                        <button onClick={() => enableUpdate('lastName')}>Edit</button>
                                    </li>}

                                {change.email ?
                                    <>
                                        <input type="text" value={update.email} onChange={(e) => { updateField(e, 'email') }} />
                                        <button onClick={() => {
                                            updateRequest('email');
                                        }
                                        }>Save</button>
                                    </>
                                    : <li>Email: {data.email}
                                        <button onClick={() => enableUpdate('email')}>Edit</button>
                                    </li>}

                                <li>Games Won: {data.wins}</li>
                                <li>Games Played: {data.games}</li>
                                <button onClick={() => enableUpdate('password')} > change password </button>
                                <br />
                                <Link to="/game">New Game</Link>
                                <br />
                            </>}

                    </>
                    : <>
                        <li>Email: {data.email}</li>
                        <Link to="/dashboard">dashboard</Link>
                        <br />
                    </>

                }


            </ul>

            <button onClick={() => {
                localStorage.removeItem('token');
                window.location.href = '/';
            }
            }>Logout</button>
        </div>
    )
}

export default Profile;
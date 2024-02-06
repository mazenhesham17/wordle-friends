import React, { useState } from 'react'

export const Profile = () => {
    const [data, setData] = useState({});
    const token = localStorage.getItem('token');
    fetch('http://localhost:4000/profile', {
        method: 'GET',
        headers: {
            'Authorization': token
        }
    })
        .then(response => response.json())
        .then(body => {
            setData(body);
        })
        .catch(err => console.error(err));
    return (
        <div>
            <h1>Profile</h1>
            <ul>
                <li>Username: {data.username}</li>
            </ul>
        </div>
    )
}

export default Profile;

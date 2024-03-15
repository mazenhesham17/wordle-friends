import React, { useState, useContext, useEffect } from 'react'
import { useNavigate } from 'react-router-dom';
import { Avatar } from 'primereact/avatar';
import styles from './Styles/informationcard.module.css';
import { useDispatch } from 'react-redux';
import { reduxLogout } from '../../State/authSlice';
import { FunctionContext } from '../../App';

export const InformationCard = () => {
    const navigate = useNavigate();
    const dispatch = useDispatch();
    const showErrorMessage = useContext(FunctionContext);
    const token = localStorage.getItem('token');
    const [showMenu, setShowMenu] = useState(false);
    const [loading, setLoading] = useState(true);
    const [data, setData] = useState({});

    const toggleMenu = () => {
        setShowMenu(!showMenu);
    }

    const fetchData = async () => {
        try {
            const response = await fetch('http://localhost:4000/api/info', {
                method: 'GET',
                headers: {
                    'Authorization': token
                }
            });
            const responseJSON = await response.json();
            if (responseJSON.error) {
                showErrorMessage(responseJSON.error);
            } else {
                setData(responseJSON);
                setLoading(false);
            }
        } catch ({ name, message }) {
            showErrorMessage(message);
        }
    }

    const logout = () => {
        localStorage.removeItem('token');
        localStorage.removeItem('userType');
        dispatch(reduxLogout());
        navigate('/login');
    }

    useEffect(() => {
        if (token) {
            fetchData();
        }
    }, [])

    if (!token)
        return null;

    return (
        <>
            {loading ? null :
                <div className={styles.column} >
                    <div className={styles.container} >
                        <Avatar label={data.username[0].toUpperCase()} shape="circle" size="normal" className={styles.avatar} />
                        <div>
                            <div className={styles.row} >
                                <h1> {data.firstName + " " + data.lastName} </h1>
                                <div onClick={toggleMenu} >
                                    <box-icon name='chevron-down' size="sm" color='#B1B2FF'></box-icon>
                                </div>
                            </div>
                            <h2> {data.username} </h2>
                        </div>
                    </div>
                    <div className={styles.menuContainer} >
                        <div className={`${styles.menu} ${showMenu ? styles.open : ''}`} >
                            <ul>
                                <li onClick={logout} >Log out</li>
                            </ul>
                        </div>
                    </div>
                </div>}
        </>
    )
}

export default InformationCard;
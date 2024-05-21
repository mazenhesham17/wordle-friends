import React, { useEffect, useState, useContext } from 'react';
import { useDispatch } from 'react-redux';
import { chageTitle, changePage } from '../State/pageSlice';
import { FunctionContext } from '../App';
import { generateUrl } from '../Util/urls';
import Card from '../Components/Dashboard/Card';
import CustomChart from '../Components/Dashboard/CustomChart';
import styles from './Styles/layout.module.css';


export const Dashboard = () => {
    const token = localStorage.getItem('token');
    const dispatch = useDispatch();
    const showErrorMessage = useContext(FunctionContext);
    const [data, setData] = useState({});

    const fetchData = async () => {
        try {
            const now = new Date();
            const offset = - now.getTimezoneOffset() / 60;
            const url = generateUrl('admin', 'dashboard', offset);
            const response = await fetch(url, {
                method: 'GET',
                headers: {
                    'Authorization': token
                }
            });
            const responseJSON = await response.json();
            if (responseJSON.error) {
                showErrorMessage(responseJSON.error);
                return;
            }
            setData(responseJSON);
        } catch ({ name, message }) {
            showErrorMessage(message);
        }
    }

    useEffect(() => {
        dispatch(changePage('dashboard'));
        dispatch(chageTitle('Dashboard'));
        fetchData();
    }, []);

    return (
        <div className={styles.column} >
            <div className={`${styles.row} ${styles.center}`}>
                <Card title="Total Players" value={data.totalPlayers} unit={'players'} />
                <Card title="Total Games" wins={data.totalWins} loses={data.totalGames - data.totalWins} unit={'games'} />
                <Card title="Total Messages" value={data.totalMessages} unit={'messages'} />
            </div>
            <div className={`${styles.row} ${styles.center}`}>
                <CustomChart title="Players" data={data.players} />
                <CustomChart title="Games" data={data.games} />
                <CustomChart title="Messages" data={data.messages} />
            </div>
        </div>

    )
}

export default Dashboard;
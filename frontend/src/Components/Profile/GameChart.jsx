import React, { useContext, useEffect, useState } from 'react'
import { Chart } from 'primereact/chart';
import { FunctionContext } from '../../App';
import styles from './Styles/chart.module.css';
import { lastNelements } from '../../Util/array';
import { monthName } from '../../Util/date';

export const GameChart = () => {
    const token = localStorage.getItem('token');
    const showErrorMessage = useContext(FunctionContext);
    const [data, setData] = useState({});

    const updateData = (gamesData) => {
        const mostRecentData = lastNelements(gamesData, 30);
        const dates = [];
        const wins = [];
        const loses = [];
        mostRecentData.forEach(element => {
            const day = element.Date.split('-')[2];
            const month = element.Date.split('-')[1];
            dates.push(`${monthName(parseInt(month))} ${parseInt(day)} `);
            wins.push(element.wins);
            loses.push(element.loses);
        });
        setData({
            labels: dates,
            datasets: [
                {
                    type: 'bar',
                    label: 'Wins',
                    data: wins,
                    backgroundColor: '#66BB6A'
                },
                {
                    type: 'bar',
                    label: 'Loses',
                    data: loses,
                    backgroundColor: '#CC3333'
                }
            ]
        });
    }


    const chartOptions = {
        plugins: {
            title: {
                display: true,
                text: 'Wins and loses',
                font: {
                    size: 24,
                    weight: '500'
                },
                position: 'bottom',
            },
            legend: {
                position: 'right',
            },
        },
        scales: {
            x: {
                stacked: true,
            },
            y: {
                stacked: true,
            }
        },
        layout: {
            padding: {
                left: 50,
                right: 20,
                top: 50,
                bottom: 0
            }
        },
        barThickness: 20,
        responsive: true
    }

    const fetchData = async () => {
        try {
            const response = await fetch('http://localhost:4000/api/profile/games-info', {
                method: 'GET',
                headers: {
                    'Authorization': token
                }
            });
            const responseJSON = await response.json();
            if (responseJSON.error) {
                showErrorMessage(responseJSON.error);
            } else {
                updateData(responseJSON.games);
            }
        } catch ({ name, message }) {
            showErrorMessage(message);
        }
    }

    useEffect(() => {
        fetchData();
    }, []);

    return (
        <div className={styles.container} >
            <div className={styles.row} >
                <box-icon name='bar-chart-alt-2' size="md" color='#B1B2FF'></box-icon>
                <h1>Statistics</h1>
            </div>
            <Chart className={styles.chart} type="bar" data={data}
                options={chartOptions} />
        </div>
    )
}

export default GameChart;
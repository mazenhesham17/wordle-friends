import React, { useEffect, useState } from 'react';
import { monthName } from '../../Util/date';
import { Chart } from 'primereact/chart';
import styles from './Styles/chart.module.css';

export const CustomChart = (props) => {
    const [formattedData, setFormattedData] = useState({});


    useEffect(() => {
        if (!props.data) return;
        const dates = [];
        props.data.forEach(element => {
            const day = element.Date.split('-')[2];
            const month = element.Date.split('-')[1];
            dates.push(`${monthName(parseInt(month))} ${parseInt(day)}`);
        });
        const columns = Object.keys(props.data[0]).slice(1);

        if (columns.length > 1) {
            [columns[0], columns[1]] = [columns[1], columns[0]];
        }
        const datasets = columns.map((column) => {
            return {
                type: 'bar',
                label: column,
                data: props.data.map(
                    element => element[column]
                ),
                backgroundColor: column === 'wins' ? '#66BB6A' : column === 'loses' ? '#CC3333' : '#AAC4FF'
            }
        });
        setFormattedData({
            labels: dates,
            datasets: datasets
        });
        console.log(formattedData);
    }, [props.data]);

    const chartOptions = {
        plugins: {
            title: {
                display: true,
                text: props.title,
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


    return (
        <div className={styles.container} >
            <Chart type="bar" data={formattedData}
                options={chartOptions} />
        </div>
    )
}

export default CustomChart;
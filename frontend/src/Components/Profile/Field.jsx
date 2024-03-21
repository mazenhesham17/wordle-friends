import React from 'react'
import styles from './Styles/field.module.css';

export const Field = (props) => {
  return (
    <div className={styles.container} >
      <h1>{props.title}</h1>
      <h2>{props.value}</h2>
    </div>
  )
}

export default Field;
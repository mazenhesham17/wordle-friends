import React from 'react';
import { useField } from 'formik';
import styles from './Styles/input.module.css';


export const InputField = ({ isUpdate = false, ...props }) => {
    const [field, meta] = useField(props);
    return (
        <fieldset className={`${styles.section} ${isUpdate ? styles.update : null}`}>
            <label htmlFor={props.id || props.name} >
                {props.label}
            </label>
            <input className={meta.touched && meta.error ? styles.error : null} {...field} {...props} />
            {meta.touched && meta.error ? (<div className={styles.error}>{meta.error}</div>) : null}
        </fieldset>
    )
}

export default InputField;
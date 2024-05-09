import React, { useContext, useRef } from 'react';
import { Form, Formik } from 'formik';
import * as Yup from 'yup';
import { FunctionContext } from '../../App';
import InputField from './InputField';
import styles from './Styles/form.module.css';

export const UpdateForm = (props) => {
    const token = localStorage.getItem('token');
    const showErrorMessage = useContext(FunctionContext);
    const formikRef = useRef(null);

    const validationSchema = Yup.object({
        firstName: Yup.string()
            .required('This field is required')
            .min(3, 'First name must be at least 3 characters long'),
        lastName: Yup.string()
            .required('This field is required')
            .min(3, 'Last name must be at least 3 characters long'),
        email: Yup.string()
            .required('This field is required')
            .matches(/^[\w._-]+@[\w.]+\.[\w]{2,4}$/, 'Invalid email address'),
    });

    const submitForm = () => {
        if (formikRef.current) {
            formikRef.current.submitForm();
        }
    };

    const submit = async (data) => {
        try {
            const response = await fetch('http://localhost:4000/api/profile/personal-info', {
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': token,
                },
                body: JSON.stringify(data),
            })
            const responseJSON = await response.json();
            if (responseJSON.error) {
                showErrorMessage(responseJSON.error);
            } else {
                window.location.reload();
            }
        } catch ({ name, message }) {
            showErrorMessage(message);
        }
    };

    return (
        <>
            <div>
                <div className={styles.heading} >
                    Personal Information
                </div>
                <Formik
                    innerRef={formikRef}
                    initialValues={props.data}
                    validationSchema={validationSchema}
                    onSubmit={async (values, { setSubmitting }) => {
                        await submit(values);
                        setSubmitting(false);
                    }}
                >
                    <Form className={styles.form} >
                        <InputField name="firstName" type="text" label="First Name" isUpdate={true} />
                        <InputField name="lastName" type="text" label="Last Name" isUpdate={true} />
                        <InputField name="email" type="email" label="Email" isUpdate={true} />
                    </Form>
                </Formik>
            </div>
            <div>
                <button className={`${styles.button} ${styles.cancel}`} onClick={() => { props.back() }} > Cancel </button>
                <button className={styles.button} onClick={() => { props.changePassword() }} > Change Password </button>
                <button className={`${styles.button} ${styles.save}`} onClick={submitForm} >Save changes</button>
            </div>
        </>
    )
}

export default UpdateForm;
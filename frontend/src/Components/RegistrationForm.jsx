import React, { useRef } from 'react'
import { Form, Formik } from 'formik';
import * as Yup from 'yup';
import InputField from './InputField';
import { hashPassword } from '../Util/encryption';
import { Link, useNavigate } from 'react-router-dom';
import "primereact/resources/themes/lara-light-indigo/theme.css";
import "primereact/resources/primereact.min.css";
import "primeicons/primeicons.css";
import { Toast } from 'primereact/toast';
import styles from './Styles/form.module.css';

export const RegistrationForm = () => {
    const navigate = useNavigate();
    const toastRef = useRef(null);
    const validationSchema = Yup.object({
        firstName: Yup.string()
            .required('This field is required')
            .min(3, 'First name must be at least 3 characters long'),
        lastName: Yup.string()
            .required('This field is required')
            .min(3, 'Last name must be at least 3 characters long'),
        username: Yup.string()
            .required('This field is required')
            .min(3, 'Username must be at least 3 characters long')
            .max(30, 'Username must be at most 30 characters long'),
        email: Yup.string()
            .required('This field is required')
            .email('Invalid email address').matches(/^[\w._-]+@[\w.]+\.[\w]{2,4}$/),
        password: Yup.string()
            .required('This field is required')
            .min(5, 'Password must be at least 5 characters long')
    })
    const submit = async (data) => {
        const hashedPassword = await hashPassword(data.password);
        const response = await fetch('http://localhost:4000/register', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                username: data.username,
                firstName: data.firstName,
                lastName: data.lastName,
                email: data.email,
                password: hashedPassword
            }),
        })
        const responseJSON = await response.json();
        if (responseJSON.error) {
            toastRef.current.show({ severity: 'error', summary: 'Error', detail: responseJSON.error });
        } else {
            localStorage.setItem('token', responseJSON.token);
            navigate('/profile');
        }
    }
    return (
        <>
            <Toast ref={toastRef} />
            <div className={styles.center}>
                <div className={styles.section}>
                    <Formik initialValues={{
                        firstName: '',
                        lastName: '',
                        username: '',
                        email: '',
                        password: '',
                    }}
                        validationSchema={validationSchema}
                        onSubmit={async (values, { setSubmitting }) => {
                            await submit(values);
                            setSubmitting(false);
                        }}
                    >
                        {({ isSubmitting }) => (
                            <Form>
                                <h1>LOG IN</h1>
                                <div className={styles.row} >
                                <InputField label="First Name" name="firstName" type="text" />
                                <InputField label="Last Name" name="lastName" type="text" />
                                </div>
                                
                                <InputField label="Username" name="username" type="text" />
                                <InputField label="Email" name="email" type="email" />
                                <InputField label="Password" name="password" type="password" />
                                <div>
                                    Already have an account ?
                                    <Link to='/login'>Login</Link>
                                </div>
                                <button type='submit' disabled={isSubmitting}>Register</button>
                            </Form>
                        )}
                    </Formik>
                </div>
            </div>
        </>
    )
}

export default RegistrationForm;
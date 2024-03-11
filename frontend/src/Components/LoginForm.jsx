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

export const LoginForm = () => {
    const navigate = useNavigate();
    const toastRef = useRef(null);
    const validationSchema = Yup.object({
        identifier: Yup.string()
            .required('This field is required')
            .test('identifier', 'Invalid email or username', (value) => {
                if (value) {
                    const usernameRegex = /^[\w_]{3,30}$/;
                    if (usernameRegex.test(value)) {
                        return true;
                    }
                    const emailRegex = /^[\w._-]+@[\w.]+\.[\w]{2,4}$/;
                    if (emailRegex.test(value)) {
                        return true;
                    }
                }
                return false;
            }),
        password: Yup.string()
            .required('This field is required')
            .min(5, 'Password must be at least 5 characters long')
    })
    const submit = async (data) => {
        const hashedPassword = await hashPassword(data.password);
        console.log(hashedPassword);
        const response = await fetch('http://localhost:4000/login', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ identifier: data.identifier, password: hashedPassword }),
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
                        identifier: '',
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
                                <InputField label='Email or username' name='identifier' type='text' />
                                <InputField label='Password' name='password' type='password' />
                                <div>
                                    Don't have an account ?
                                    <Link to='/register'>Register</Link>
                                </div>
                                <button type='submit' disabled={isSubmitting}>Log In</button>
                            </Form>
                        )}
                    </Formik>
                </div>
            </div>
        </>
    )
}

export default LoginForm;

import React, { useContext, useRef } from 'react'
import { Form, Formik } from 'formik';
import * as Yup from 'yup';
import InputField from './InputField';
import styles from './Styles/form.module.css';
import { FunctionContext } from '../../App';
import { hashPassword } from '../../Util/encryption';

export const PasswordUpdate = (props) => {
  const token = localStorage.getItem('token');
  const showErrorMessage = useContext(FunctionContext);
  const formikRef = useRef(null);

  const submitForm = () => {
    if (formikRef.current) {
      formikRef.current.submitForm();
    }
  };
  const validationSchema = Yup.object({
    password: Yup.string()
      .required('This field is required')
      .min(5, 'Password must be at least 5 characters long')
  })

  const submit = async (data) => {
    try {
      const hashedPassword = await hashPassword(data.password);
      const response = await fetch('http://localhost:4000/api/profile/personal-info', {
        method: 'PUT',
        headers: {
          'Content-Type': 'application/json',
          'Authorization': token,
        },
        body: { password: hashedPassword },
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
  }

  return (
    <>
      <div>
        <div className={styles.heading} >
          Change Password
        </div>
        <Formik
          innerRef={formikRef}
          initialValues={{
            password: ''
          }}
          validationSchema={validationSchema}
          onSubmit={async (values, { setSubmitting }) => {
            await submit(values);
            setSubmitting(false);
          }}
        >
          <Form className={styles.form} >
            <InputField label="Password" name="password" type="password" isUpdate={true} />
          </Form>
        </Formik>
      </div>
      <div>
        <button className={`${styles.button} ${styles.cancel} `} onClick={() => { props.back() }} > Cancel </button>
        <button className={`${styles.button} ${styles.save}`} onClick={submitForm} >Save changes</button>
      </div>
    </>
  )
}

export default PasswordUpdate;
import React, { useContext, useRef } from 'react';
import { Form, Formik } from 'formik';
import * as Yup from 'yup';
import { FunctionContext } from '../../App';
import { hashPassword } from '../../Util/encryption';
import { generateUrl } from '../../Util/urls';
import InputField from './InputField';
import styles from './Styles/form.module.css';


export const PasswordUpdate = (props) => {
  const token = localStorage.getItem('token');
  const showErrorMessage = useContext(FunctionContext);
  const formikRef = useRef(null);

  const validationSchema = Yup.object({
    password: Yup.string()
      .required('This field is required')
      .min(5, 'Password must be at least 5 characters long')
  });

  const submitForm = () => {
    if (formikRef.current) {
      formikRef.current.submitForm();
    }
  };

  const submit = async (data) => {
    try {
      const hashedPassword = await hashPassword(data.password);
      const url = generateUrl('profile', 'personal-info');
      const response = await fetch(url, {
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
  };

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
        <button className={`${styles.button} ${styles.cancel}`} onClick={() => { props.back() }} > Cancel </button>
        <button className={`${styles.button} ${styles.save}`} onClick={submitForm} >Save changes</button>
      </div>
    </>
  )
}

export default PasswordUpdate;
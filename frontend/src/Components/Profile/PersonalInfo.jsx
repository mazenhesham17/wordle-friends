import React, { useContext, useEffect, useState } from 'react'
import { Avatar } from 'primereact/avatar';
import { FunctionContext } from '../../App';
import { Field } from './Field';
import UpdateForm from '../Form/UpdateForm';
import PasswordUpdate from '../Form/PasswordUpdate';
import styles from './Styles/personalinfo.module.css';


export const PersonalInfo = () => {
  const token = localStorage.getItem('token');
  const showErrorMessage = useContext(FunctionContext);
  const [selector, setSelector] = useState('personal-info');
  const [data, setData] = useState({});
  const [loading, setLoading] = useState(true);

  const fetchData = async () => {
    try {
      const response = await fetch('http://localhost:4000/api/profile/personal-info', {
        method: 'GET',
        headers: {
          'Authorization': token,
        }
      });
      const responseJSON = await response.json();
      if (responseJSON.error) {
        showErrorMessage(responseJSON.error);
      } else {
        setData(responseJSON);
        setLoading(false);
      }
    }
    catch ({ name, message }) {
      showErrorMessage(message);
    }
  }


  const chageSelector = (value) => {
    setSelector(value);
  }

  useEffect(() => {
    fetchData();
  }, []);

  return (
    loading ? <div>Loading...</div> :
      <div className={styles.container} >
        {selector === 'personal-info' ?
          <>
            <div>
              <div className={styles.image_container} >
                <div className={styles.image} >
                  <Avatar label={`${data?.firstName[0].toUpperCase()}${data?.lastName[0].toUpperCase()}`}
                    shape="circle" className={styles.avatar} />
                </div>
              </div>
              <div className={styles.row} >
                <h1>{data?.firstName}</h1>
                <h1>{data?.lastName}</h1>
              </div>
              <div className={styles.heading} >
                Personal Information
              </div>
              <Field title="username" value={data?.username} />
              <Field title="Email" value={data?.email} />
            </div>
            <button className={styles.button} onClick={() => { chageSelector('edit-profile') }}  >Edit profile</button>
          </>
          : selector === 'edit-profile' ?
            <UpdateForm data={data} changePassword={() => { chageSelector('password') }} back={() => { chageSelector('personal-info') }} />
            : <PasswordUpdate back={() => { chageSelector('personal-info') }} />}
      </div>

  )
}

export default PersonalInfo;
import React, { useContext, useState } from 'react'
import styles from './Styles/card.module.css';
import { Avatar } from 'primereact/avatar';
import { FunctionContext } from '../../App';
import { generateUrl } from '../../Util/urls';

export const Card = (props) => {
  const token = localStorage.getItem('token');
  const showErrorMessage = useContext(FunctionContext);
  const [isFriend, setIsFriend] = useState(props.isFriend);

  const addFriend = async () => {
    try {
      const url = generateUrl('add-friend', props.playerID);
      const response = await fetch(url, {
        method: 'POST',
        headers: {
          'Authorization': token
        },
      });
      const responseJSON = await response.json();
      if (responseJSON.error) {
        showErrorMessage(responseJSON.error);
      } else {
        if (responseJSON.message === "success") {
          setIsFriend(!isFriend);
        }
      }
    } catch ({ name, message }) {
      showErrorMessage(message);
    }
  }

  if (props.isEmpty) {
    return (
      <div className={styles.container} >
        <p>There is no player with this username </p>
      </div>
    )
  }

  return (
    <div className={styles.container} >
      <Avatar label={props.firstName[0].toUpperCase() + props.lastName[0].toUpperCase()}
        style={{ backgroundColor: props.color }}
        shape='circle' size='xlarge' className={styles.avatar} />
      <div className={styles.column} >
        <h1> {props.firstName + ' ' + props.lastName} </h1>
        <h2> {props.username} </h2>
        <div className={styles.end}>
          <div className={`${styles.button} ${isFriend ? '' : styles.add} `}
            onClick={() => {
              if (!isFriend) {
                addFriend()
              }
            }} >
            {isFriend ?
              <>
                <box-icon name='user-check' size="sm" color='white'></box-icon>
                <p>friend</p>
              </> :
              <>
                <box-icon name='user-plus' size="sm" color='white' ></box-icon>
                <p>add friend</p>
              </>
            }
          </div>
        </div>
      </div>
    </div>
  )
}

export default Card;
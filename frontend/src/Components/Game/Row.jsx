import React, { useEffect } from 'react'
import styles from './Styles/row.module.css';

export const Row = (props) => {

  // handle animation one after another
  useEffect(() => {
    if (!props.template) return;
    const spans = document.querySelectorAll(`.${styles.container} .${styles.selected}`);
    spans.forEach((span, index) => {
      setTimeout(() => {
        span.classList.remove(styles.selected);
        if (props.template[index] === '+') {
          span.classList.add(styles.correct);
        } else if (props.template[index] === '-') {
          span.classList.add(styles.paritial_correct);
        } else {
          span.classList.add(styles.incorrect);
        }
        span.setAttribute('data-animation', 'flip');
      }, index * 300);
    });
  }, [props.template]);

  return (
    <div className={styles.container}>
      {Array.from({ length: props.len }, (_, index) => (

        <span key={index}
          className={`${index < props.word.length ? styles.selected : styles.unselected
            }`}
          data-animation={"none"}
        >
          {props.word[index]}
        </span>

      ))}
    </div>
  )
}

export default Row;
import React, { useEffect, useState } from 'react'
import { AiOutlineEnter } from "react-icons/ai";
import { HiOutlineBackspace } from "react-icons/hi";
import styles from './Styles/keyboard.module.css';
import { useDispatch, useSelector } from 'react-redux';
import { changeInput, toggleClear } from '../../State/gameSlice';


export const Keyboard = (props) => {
    const dispatch = useDispatch();
    const clear = useSelector(state => state.game.clear);
    const [input, setInput] = useState('');
    const [pressedKey, setPressedKey] = useState('');
    const buttons = [
        "Q W E R T Y U I O P",
        "A S D F G H J K L",
        "Backspace Z X C V B N M Enter",
    ]

    const onKeyPress = (e) => {
        if (e.key !== "Enter" && e.key !== "Backspace" && e.key.length !== 1) {
            return;
        }
        setPressedKey(e.key);
        press(e.key);
    }


    const press = (val) => {
        setInput((prev) => {
            if (val === "Backspace") {
                return prev.slice(0, -1);
            }
            if (val === "Enter") {
                setTimeout(() => {
                    props.onEnter();
                }, 50);
                return prev;
            }
            if (prev.length < props.len) {
                return prev + val;
            }
            return prev;
        });
    }

    useEffect(() => {
        dispatch(changeInput(input));
    }, [input]);

    useEffect(() => {
        if (clear) {
            setInput('');
            dispatch(toggleClear())
        }
    }, [clear]);

    useEffect(() => {
        document.addEventListener('keydown', onKeyPress);
        return () => {
            document.removeEventListener('keydown', onKeyPress);
        }
    }, []);

    return (
        <div className={styles.container} >
            {
                buttons.map((row, index) => (
                    <div key={index} className={styles.row}>
                        {
                            row.split(' ').map((keyName, idx) => (
                                <div key={idx}
                                    className={`${styles.key} ${pressedKey.toLowerCase() === keyName.toLowerCase() && styles.pressed}`}
                                    state={props.keys.has(keyName.toLowerCase()) ? props.keys.get(keyName.toLowerCase()) : 'none'}
                                    onClick={() => press(keyName)} >{
                                        keyName.length === 1 ? keyName : keyName === "Backspace" ?
                                            <HiOutlineBackspace size={24} /> : <AiOutlineEnter size={24} />
                                    }</div>
                            ))
                        }
                    </div>
                ))
            }
        </div>
    )
}

export default Keyboard;
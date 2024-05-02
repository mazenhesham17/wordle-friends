import React, { useState, useEffect, useContext } from 'react'
import Row from './Row';
import styles from './Styles/gameboard.module.css';
import Keyboard from './Keyboard';
import { useDispatch, useSelector } from 'react-redux';
import { useParams, useBeforeUnload, useNavigate } from 'react-router-dom';
import { chageTitle } from '../../State/pageSlice';
import { toggleClear } from '../../State/gameSlice';
import { FunctionContext } from '../../App';
import OpponentCard from './OpponentCard';

export const GameBoard = () => {
  const token = localStorage.getItem('token');
  const showErrorMessage = useContext(FunctionContext);
  const dispatch = useDispatch();
  const navigate = useNavigate();
  const { urlRoomID } = useParams();
  const currentWord = useSelector(state => state.game.inputValue);
  const [blocking, setBlocking] = useState(false);
  const [blockingFlag, setBlockingFlag] = useState(false);
  const turns = 6, wordLength = 5;
  const [idx, setIdx] = useState(0);
  const [backFlag, setBackFlag] = useState(false);
  const [isDuo, setIsDuo] = useState(false);
  const [waiting, setWaiting] = useState(true);
  const [timeout, setTimeout] = useState(false);
  const [opponent, setOpponent] = useState({
    firstName: 'o',
    lastName: 'n',
    username: 'opponent',
  });
  const [opponentTemplate, setOpponentTemplate] = useState('');
  const [words, setWords] = useState(new Array(turns).fill(''));
  const [templates, setTemplates] = useState(new Array(turns).fill(''));
  const [sendFlag, setSendFlag] = useState(false);
  const [template, setTemplate] = useState('');
  const [templateFlag, setTemplateFlag] = useState(false);
  const [typedKeys, setTypedKeys] = useState(new Map());
  const [finsihed, setFinished] = useState(false);
  const [won, setWon] = useState(false);
  const [ws, updateWS] = useState(null);

  const toggleBlockingFlag = () => {
    setBlockingFlag(!blockingFlag);
  }

  const toggleBlocking = () => {
    setBlocking(!blocking);
  }

  const toggleSendFlag = () => {
    setSendFlag(!sendFlag);
  }

  const toggleTemplateFlag = () => {
    setTemplateFlag(!templateFlag);
  }

  const finishGame = (won) => {
    setFinished(true);
    setWon(won);
    toggleBlockingFlag();
  }

  const increment = () => {
    setIdx(idx + 1);
  }

  const navigateBackToGamePage = () => {
    navigate('/game');
  }

  const createSocket = () => {
    const webSocket = new WebSocket('ws://localhost:8080');
    updateWS(webSocket);
    webSocket.onopen = () => {
      console.log('WebSocket Client Connected');
      const gameID = urlRoomID.split('G')[1];
      webSocket.send(gameID);
    };
    webSocket.onmessage = socketOnMessage;
    webSocket.onclose = () => {
      console.log('WebSocket Client Disconnected');
    };
  }

  const socketOnMessage = (message) => {
    const response = message.data;
    if (response.startsWith('Result: ')) {
      setTemplate(response.split(' ')[1]);
      toggleTemplateFlag();
    } else if (response.startsWith('Opponent')) {
      setOpponentTemplate(response.split(' ')[2]);
    } else if (response.startsWith('{')) {
      setOpponent(JSON.parse(response));
    } else {
      if (response.includes('win')) {
        finishGame(true);
      } else if (response.includes('lose')) {
        finishGame(false);
      } else {
        if (response.includes('start')) {
          setWaiting(false);
          toggleBlockingFlag();
        } else if (response === 'Time out!') {
          setTimeout(true);
        }
      }
    }
  }

  const sendMessage = (message) => {
    ws.send(message);
  }

  const closeSocket = () => {
    if (ws)
      ws.close();
  }

  // prevent the user from leaving the page
  useBeforeUnload((event) => {
    console.log(blocking);
    if (blocking) {
      const message = 'Are you sure you want to leave this page? Your changes may not be saved.';
      event.returnValue = message;
      return message;
    }
  });

  // change the title of the page based on the roomID
  useEffect(() => {
    if (urlRoomID) {
      if (urlRoomID.includes('S')) {
        dispatch(chageTitle('Single Player'));
      } else {
        dispatch(chageTitle('Duo Player'));
        setIsDuo(true);
      }
      // start the game
      startGame();
    }
  }, [urlRoomID]);

  // start the game
  const startGame = async () => {
    try {
      const response = await fetch(`http://localhost:4000/api/game/start/${urlRoomID}`, {
        method: 'Post',
        headers: {
          'Authorization': token
        },
      });
      const responseJSON = await response.json();
      if (responseJSON.error) {
        showErrorMessage(responseJSON.error);
        return;
      }
      setBackFlag(true);
    }
    catch ({ name, message }) {
      showErrorMessage(message);
    }
  }

  // update the input value
  useEffect(() => {
    if (idx < turns) {
      setWords((prev) => {
        const newWords = [...prev];
        newWords[idx] = currentWord;
        return newWords;
      });
    }

  }, [currentWord]);

  // open the socket
  useEffect(() => {
    if (backFlag) {
      createSocket();
    }
    return () => {
      closeSocket();
    }
  }, [backFlag]);

  useEffect(() => {
    if (sendFlag) {
      if (currentWord.length === wordLength) {
        sendMessage(currentWord);
      } else {
        showErrorMessage(`Word length should be ${wordLength} characters long.`);
      }
      toggleSendFlag();
    }
  }, [sendFlag]);

  useEffect(() => {
    if (blockingFlag) {
      toggleBlocking();
      toggleBlockingFlag();
    }
  }, [blockingFlag]);

  useEffect(() => {
    if (templateFlag) {
      setTemplates((prev) => {
        const newTemplates = [...prev];
        newTemplates[idx] = template;
        return newTemplates;
      });
      const newTypedKeys = new Map(typedKeys);
      template.split('').forEach((char, index) => {
        if (char === '+') {
          newTypedKeys.set(words[idx][index].toLowerCase(), 'correct');
        } else if (char === '-') {
          newTypedKeys.set(words[idx][index].toLowerCase(), 'partial-correct');
        } else {
          newTypedKeys.set(words[idx][index].toLowerCase(), 'incorrect');
        }
      });
      setTypedKeys(newTypedKeys);
      increment();
      setTemplate('');
      toggleTemplateFlag();
      dispatch(toggleClear());
    }
  }, [templateFlag]);



  return (
    <div className={styles.main_container} >
      {isDuo && <OpponentCard roomID={urlRoomID} waiting={waiting} timeOut={timeout} template={opponentTemplate} {...opponent} />}
      <div className={styles.container}>
        <div className={styles.inner_container} >
          {
            words.map((word, index) => (
              <Row key={index} len={wordLength} word={word} template={templates[index]} />
            ))
          }
          {finsihed && <div className={styles.row} >
            <div className={styles.alert} state={won ? "win" : "lose"}>
              <box-icon name={won ? 'happy-heart-eyes' : 'sad'} color='white' ></box-icon>
              <p>{won ? 'You won' : 'You lost'}</p>
            </div>
            <button onClick={navigateBackToGamePage} >New game</button>
          </div>}
        </div>
        <Keyboard keys={typedKeys} onEnter={toggleSendFlag} len={wordLength} disabled={waiting || finsihed} />
      </div>

    </div>
  )
}

export default GameBoard;
import React, { useState, useEffect, useContext, useReducer } from 'react'
import { useParams, useBeforeUnload, useNavigate } from 'react-router-dom';
import { useDispatch, useSelector } from 'react-redux';
import { chageTitle } from '../../State/pageSlice';
import { toggleClear } from '../../State/gameSlice';
import { FunctionContext } from '../../App';
import Row from './Row';
import Keyboard from './Keyboard';
import OpponentCard from './OpponentCard';
import styles from './Styles/gameboard.module.css';

const initialGameInfo = {
  turns: 6,
  wordLength: 5,
  currnetIdx: 0,
  waiting: true,
  timeout: false,
  isDuo: false,
  opponent: {
    firstName: '',
    lastName: '',
    username: 'opponent',
  },
  isFinished: false,
  won: false
}

const infoReducer = (state, action) => {
  switch (action.type) {
    case 'duo':
      return { ...state, isDuo: true };
    case 'start':
      return { ...state, waiting: false };
    case 'timeout':
      return { ...state, timeout: true };
    case 'opponent':
      return { ...state, opponent: action.payload };
    case 'increment':
      return { ...state, currnetIdx: state.currnetIdx + 1 };
    case 'finish':
      return { ...state, isFinished: true, won: action.payload };

    default:
      return state;
  }
}

const initialGameState = {
  words: new Array(initialGameInfo.turns).fill(''),
  templates: new Array(initialGameInfo.turns).fill(''),
  sendFlag: false,
  template: '',
  opponentTemplate: '',
  templateFlag: false,
  typedKeys: new Map()
}

const gameReducer = (state, action) => {
  switch (action.type) {
    case 'toggleSend':
      return { ...state, sendFlag: !state.sendFlag };
    case 'template':
      return { ...state, template: action.payload.template, templateFlag: true };
    case 'toggleTemplateFlag':
      return { ...state, templateFlag: !state.templateFlag };
    case 'newTemplate': {
      const { index } = action.payload;
      const newTemplates = [...state.templates];
      newTemplates[index] = state.template;
      const newTypedKeys = new Map(state.typedKeys);
      state.template.split('').forEach((char, idx) => {
        if (char === '+') {
          newTypedKeys.set(state.words[index][idx].toLowerCase(), 'correct');
        } else if (char === '-') {
          newTypedKeys.set(state.words[index][idx].toLowerCase(), 'partial-correct');
        } else {
          newTypedKeys.set(state.words[index][idx].toLowerCase(), 'incorrect');
        }
      });
      return { ...state, templates: newTemplates, typedKeys: newTypedKeys };
    }

    case 'opponentTemplate':
      return { ...state, opponentTemplate: action.payload.opponentTemplate };
    case 'newWord': {
      const { index, word } = action.payload;
      const newWords = [...state.words];
      newWords[index] = word;
      return { ...state, words: newWords };
    }
    default:
      return state;
  }
}

export const GameBoard = () => {
  const token = localStorage.getItem('token');
  const navigate = useNavigate();
  const dispatch = useDispatch();
  const { urlRoomID } = useParams();
  const showErrorMessage = useContext(FunctionContext);
  const currentWord = useSelector(state => state.game.inputValue);

  const [gameInfo, infoDispatch] = useReducer(infoReducer, initialGameInfo);
  const [gameState, gameDispatch] = useReducer(gameReducer, initialGameState);

  const [ws, updateWS] = useState(null);

  const navigateBackToGamePage = () => {
    navigate('/game');
  }

  const socketOnMessage = (message) => {
    const response = message.data;
    if (response.startsWith('Result: ')) {
      gameDispatch({ type: 'template', payload: { template: response.split(' ')[1] } });
    } else if (response.startsWith('Opponent')) {
      gameDispatch({ type: 'opponentTemplate', payload: { opponentTemplate: response.split(' ')[2] } });
    } else if (response.startsWith('{')) {
      infoDispatch({ type: 'opponent', payload: JSON.parse(response) });
    } else {
      if (response.includes('win')) {
        infoDispatch({ type: 'finish', payload: true });
      } else if (response.includes('lose')) {
        infoDispatch({ type: 'finish', payload: false });
      } else {
        if (response.includes('start')) {
          infoDispatch({ type: 'start' });
        } else if (response === 'Time out!') {
          infoDispatch({ type: 'timeout' });
        }
      }
    }
  }

  const createSocket = () => {
    const webSocket = new WebSocket('ws://localhost:8080');
    updateWS(webSocket);
    webSocket.onopen = () => {
      const gameID = urlRoomID.split('G')[1];
      webSocket.send(gameID);
    };
    webSocket.onmessage = socketOnMessage;
  }

  const sendMessage = (message) => {
    ws.send(message);
  }

  const closeSocket = () => {
    if (ws)
      ws.close();
  }

  // start the game
  const startGame = () => {
    return new Promise(async (resolve, reject) => {
      try {
        const response = await fetch(`http://localhost:4000/api/game/start/${urlRoomID}`, {
          method: 'Post',
          headers: {
            'Authorization': token
          },
        });
        const responseJSON = await response.json();
        if (responseJSON.error) {
          reject(responseJSON.error);
          return;
        }
        resolve(true);
      }
      catch ({ name, message }) {
        reject(message);
      }
    });

  }

  // prevent the user from leaving the page
  useBeforeUnload((e) => {
    const runnnig = !gameInfo.waiting && !gameInfo.isFinished;
    if (runnnig)
      return 'Are you sure you want to leave this page? Your changes may not be saved.';
    return null;
  });

  // change the title of the page based on the roomID
  useEffect(() => {
    if (!urlRoomID) return;
    if (urlRoomID.includes('S')) {
      dispatch(chageTitle('Single Game'));
    } else {
      dispatch(chageTitle('Duo Game'));
      infoDispatch({ type: 'duo' });
    }
    // start the game
    startGame()
      .then(() => {
        createSocket();
      })
      .catch((error) => {
        showErrorMessage(error);
      });
    return () => {
      closeSocket();
    }
  }, [urlRoomID]);

  // update the input value
  useEffect(() => {
    const { turns, currnetIdx } = gameInfo;
    if (currnetIdx < turns) {
      gameDispatch({ type: 'newWord', payload: { index: currnetIdx, word: currentWord } });
    }

  }, [currentWord]);

  useEffect(() => {
    if (!gameState.sendFlag) return;
    if (currentWord.length === gameInfo.wordLength) {
      sendMessage(currentWord);
    } else {
      showErrorMessage(`Word length should be ${gameInfo.wordLength} characters long.`);
    }
    gameDispatch({ type: 'toggleSend' });
  }, [gameState.sendFlag]);


  useEffect(() => {
    if (!gameState.templateFlag) return;
    gameDispatch({ type: 'newTemplate', payload: { index: gameInfo.currnetIdx } });
    infoDispatch({ type: 'increment' });
    gameDispatch({ type: 'toggleTemplateFlag' });
    dispatch(toggleClear());
  }, [gameState.templateFlag]);

  return (
    <div className={styles.main_container} >
      {gameInfo.isDuo && <OpponentCard roomID={urlRoomID} waiting={gameInfo.waiting} timeOut={gameInfo.timeout} template={gameState.opponentTemplate} {...gameInfo.opponent} />}
      <div className={styles.container}>
        <div className={styles.inner_container} >
          {
            gameState.words.map((word, index) => (
              <Row key={index} len={gameInfo.wordLength} word={word} template={gameState.templates[index]} />
            ))
          }
          {gameInfo.isFinished && <div className={styles.row} >
            <div className={styles.alert} state={gameInfo.won ? "win" : "lose"}>
              <box-icon name={gameInfo.won ? 'happy-heart-eyes' : 'sad'} color='white' ></box-icon>
              <p>{gameInfo.won ? 'You won' : 'You lost'}</p>
            </div>
            <button onClick={navigateBackToGamePage} >New game</button>
          </div>}
        </div>
        <Keyboard keys={gameState.typedKeys} onEnter={() => { gameDispatch({ type: 'toggleSend' }) }} len={gameInfo.wordLength} disabled={gameInfo.waiting || gameInfo.finsihed} />
      </div>

    </div>
  )
}

export default GameBoard;
#include "GameController.h"

GameController *GameController::instance = nullptr;


GameController *GameController::getInstance()
{
    if (instance == nullptr)
    {
        instance = new GameController();
    }
    return instance;
}

std::string GameController::newSinglePlayerGame(const std::string &word, const int &playerId)
{
    int gameID = addGame(word.c_str());
    addPlayerToGame(playerId, gameID);
    return GameWebView::getInstance()->newGame(gameID);
}

void GameController::startGame(const int &gameId)
{
    startNewGame(gameId);
}

std::string GameController::submitGuess(const std::string &guess, const int &gameId)
{
    std::string word = getWordByGameID(gameId);
    std::string result(word.size(), '_');
    for (int i = 0; i < word.size(); i++)
    {
        word[i] = tolower(word[i]);
        if (word[i] == tolower(guess[i]))
        {
            result[i] = '+' ;
        }else if ( word.find(tolower(guess[i])) != -1){
            result[i] = '-';
        }
    }
    result = "Result: " + result;
    return result;
}
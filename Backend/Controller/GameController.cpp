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
    dbStartGame(gameId);
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
            result[i] = '+';
        }
        else if (word.find(tolower(guess[i])) != -1)
        {
            result[i] = '-';
        }
    }
    result = "Result: " + result;
    return result;
}

void GameController::winGame(const int &gameId, const int &playerId)
{
    dbWinGame(playerId, gameId);
}

bool GameController::match(const std::string &guess, const int &gameId)
{
    std::string word = getWordByGameID(gameId);
    return word == guess;
}

void GameController::endGame(const int &gameId)
{
    dbEndGame(gameId);
}
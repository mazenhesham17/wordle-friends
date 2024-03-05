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

int GameController::newGame(const std::string &word)
{
    int gameID = addGame(word.c_str());
    return gameID;
}

void GameController::joinGame(const int &gameId, const int &playerId)
{
    addPlayerToGame(playerId, gameId);
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

std::string GameController::mergeTemplates(const std::string &template1, const std::string &template2)
{
    std::string result(template1.size(), '_');
    for (int i = 0; i < template1.size(); i++)
    {
        if (template1[i] == '+' || (i < template2.size() && template2[i] == '+'))
        {
            result[i] = '+';
        }
        else if (template1[i] == '-' || (i < template2.size() && template2[i] == '-'))
        {
            result[i] = '-';
        }
    }
    result = "Opponent's result: " + result;
    return result;
}

void GameController::deleteGame(const int &gameId)
{
    dbDeleteGame(gameId);
}
#ifndef BACKEND_GAMECONTROLLER_H
#define BACKEND_GAMECONTROLLER_H

#include <string>
#include <vector>
#include <set>
#include "../Database/dml.h"
#include "../Database/dql.h"

class GameController
{
    static GameController *instance;

    GameController(){};

public:
    static GameController *getInstance();

    int newGame(const std::string &word);

    bool isPlayerInGame(const int &playerID);

    void joinGame(const int &gameId, const int &playerId);

    void startGame(const int &gameId);

    std::string submitGuess(const std::string &guess, const int &gameId);

    bool match(const std::string &guess, const int &gameId);

    void winGame(const int &gameId, const int &playerId);

    void endGame(const int &gameId);

    void deleteGame(const int &gameId);

    std::string getMergedTemplate(const std::vector<std::string> &history, const int &gameId);
};

#endif // BACKEND_GAMECONTROLLER_H

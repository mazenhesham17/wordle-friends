#ifndef BACKEND_GAMECONTROLLER_H
#define BACKEND_GAMECONTROLLER_H
#include <string>
#include "../Database/dml.h"
#include "../Database/dql.h"
#include "../WebView/GameWebView.h"


class GameController {
    static GameController *instance;
    GameController() {};
    public:
    static GameController *getInstance();
    std::string newSinglePlayerGame( const std::string &word , const int &playerId);
    void startGame( const int &gameId);
    std::string submitGuess( const std::string &guess , const int &gameId);
    void winGame( const int &gameId, const int &playerId);
};


#endif //BACKEND_GAMECONTROLLER_H

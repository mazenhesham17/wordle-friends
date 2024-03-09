#include "GameSession.h"
#include "../Controller/GameController.h"

GameSession::GameSession(tcp::socket &&socket, const std::string &roomId, int playerId)
    : Session(std::move(socket), roomId, playerId)
{
    gameController = GameController::getInstance();
}

bool GameSession::isFinished()
{
    return turnsLeft == 0;
}
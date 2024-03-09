#ifndef BACKEND_GAMESESSION_H
#define BACKEND_GAMESESSION_H

#include "Session.h"

class GameController;

class GameSession : public Session
{
protected:
    GameController *gameController;

    int gameID;
    std::string oldTemplate;
    int turnsLeft = 6;

public:
    GameSession(tcp::socket &&socket, const std::string &roomId, int playerId);

    bool isFinished() override;
};

#endif // BACKEND_GAMESESSION_H

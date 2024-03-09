#ifndef BACKEND_SINGLEGAMESESSION_H
#define BACKEND_SINGLEGAMESESSION_H

#include "GameSession.h"

class SingleGameSession : public GameSession
{

public:
    SingleGameSession(tcp::socket &&socket, std::string roomID, int playerID);

    void launchSession() override;
};

#endif // BACKEND_SINGLEGAMESESSION_H

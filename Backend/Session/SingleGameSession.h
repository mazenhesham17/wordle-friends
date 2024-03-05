#ifndef BACKEND_SINGLEGAMESESSION_H
#define BACKEND_SINGLEGAMESESSION_H

#include "Session.h"

class SingleGameSession : public Session
{
    int gameID;

public:
    SingleGameSession(tcp::socket &&socket, int playerID);

    bool isFinished() override;

    void launchSession(const std::string &roomID) override;

    ~SingleGameSession() = default;
};

#endif // BACKEND_SINGLEGAMESESSION_H

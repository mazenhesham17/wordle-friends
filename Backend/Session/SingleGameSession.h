#ifndef BACKEND_SINGLEGAMESESSION_H
#define BACKEND_SINGLEGAMESESSION_H

#include "Session.h"

class SingleGameSession : public Session
{
public:
    void launchSession(Room &room) override;
};

#endif // BACKEND_SINGLEGAMESESSION_H

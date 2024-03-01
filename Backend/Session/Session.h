#ifndef BACKEND_SESSION_H
#define BACKEND_SESSION_H

#include "../Controller/GameController.h"
#include "../Controller/RoomController.h"
#include "../Model/Room.h"

class Session
{
protected:
    GameController *gameController;
    RoomController *roomController;

public:
    Session();
    virtual void launchSession(Room &room) = 0;
};

#endif // BACKEND_SESSION_H

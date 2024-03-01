#ifndef BACKEND_DUOGAMESESSION_H
#define BACKEND_DUOGAMESESSION_H

#include "Session.h"

class DuoGameSession : public Session
{
public:
    void launchSession(Room &room) override;
};

#endif // BACKEND_DUOGAMESESSION_H

#ifndef BACKEND_DUOGAMESESSION_H
#define BACKEND_DUOGAMESESSION_H

#include "GameSession.h"

class DuoGameSession : public GameSession
{
public:
    DuoGameSession(tcp::socket &&socket, std::string roomID, int playerID);

    void onRead(beast::error_code ec, std::size_t bytes_transferred) override;

    void onWrite(beast::error_code ec, std::size_t bytes_transferred) override;

    void launchSession() override;
};

#endif // BACKEND_DUOGAMESESSION_H

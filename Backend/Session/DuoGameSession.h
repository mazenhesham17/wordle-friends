#ifndef BACKEND_DUOGAMESESSION_H
#define BACKEND_DUOGAMESESSION_H

#include "Session.h"

class DuoGameSession : public Session
{
    std::string oldTemplate;

    std::string roomID;

    int gameID;

    int turnsLeft = 6;

public:
    DuoGameSession(tcp::socket &&socket, std::string roomID, int playerID);

    bool isFinished() override;

    void onRead(beast::error_code ec, std::size_t bytes_transferred) override;

    void onWrite(beast::error_code ec, std::size_t bytes_transferred) override;

    void launchSession(const std::string &roomID) override;

    ~DuoGameSession() = default;
};

#endif // BACKEND_DUOGAMESESSION_H

#ifndef BACKEND_CHATSESSION_H
#define BACKEND_CHATSESSION_H

#include "Session.h"
#include <string>

class ChatController;

class ChatSession : public Session
{
    int chatID;
    ChatController *chatController;

public:
    ChatSession(tcp::socket &&socket, const std::string &roomId, int playerId);

    void onRead(beast::error_code ec, std::size_t bytes_transferred) override;

    void launchSession() override;

    bool isFinished() override;
};

#endif // BACKEND_CHATSESSION_H

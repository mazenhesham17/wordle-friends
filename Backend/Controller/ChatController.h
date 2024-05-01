#ifndef BACKEND_CHATCONTROLLER_H
#define BACKEND_CHATCONTROLLER_H

#include <string>
#include <vector>
#include "../Database/dml.h"
#include "../Database/dql.h"
#include "../Model/Message.h"
#include "../WebView/ChatWebView.h"

class ChatController
{
    static ChatController *instance;

    ChatWebView *chatWebView;

    ChatController();

public:
    static ChatController *getInstance();
    bool isChatExist(const int &chatID);
    bool isPlayerInChat(const int &chatID, const int &playerID);
    Message retrieveMessageFromDB(const int &messageID);
    std::string getChat(const int &chatID, const int &playerID);
    void readChat(const int &chatID, const int &playerID);
    int getChatID(const int &playerID, const int &friendID);
    int getChatID(const std::string &roomID);
    int addChat(const int &playerID, const int &friendID);
    std::string addMessage(const int &senderID, const int &chatID, const std::string &content);
};

#endif // BACKEND_CHATCONTROLLER_H

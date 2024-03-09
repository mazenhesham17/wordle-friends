#ifndef BACKEND_CHATWEBVIEW_H
#define BACKEND_CHATWEBVIEW_H

#include <string>
#include <vector>
#include <utility>
#include <iostream>

class ChatWebView
{
    static ChatWebView *instance;
    ChatWebView(){};

public:
    static ChatWebView *getInstance();
    std::string message(const int &playerID, const std::string &message, const std::string &sendTime);
    std::string getChat(const std::vector<std::pair<int, std::pair<std::string, std::string>>> &messages);
};

#endif // BACKEND_CHATWEBVIEW_H

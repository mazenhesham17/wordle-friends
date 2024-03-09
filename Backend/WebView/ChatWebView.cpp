#include "ChatWebView.h"

ChatWebView *ChatWebView::instance = nullptr;

ChatWebView *ChatWebView::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ChatWebView();
    }
    return instance;
}

std::string ChatWebView::message(const int &playerID, const std::string &message, const std::string &sendTime)
{
    std::string result = R"({"message":")" + message + R"(","playerID":")" + std::to_string(playerID) + R"(","sendTime":")" + sendTime + R"("})";
    return result;
}

std::string ChatWebView::getChat(const std::vector<std::pair<int, std::pair<std::string, std::string>>> &messages)
{
    std::string chatView = R"([)";
    for (auto &msg : messages)
    {
        chatView += message(msg.first, msg.second.first, msg.second.second) + ",";
    }
    if (!messages.empty())
    {
        chatView.pop_back();
    }
    chatView += "]";
    return chatView;
}

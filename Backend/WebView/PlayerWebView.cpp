#include "PlayerWebView.h"

PlayerWebView *PlayerWebView::instance = nullptr;

PlayerWebView *PlayerWebView::getInstance()
{
    if (instance == nullptr)
        instance = new PlayerWebView();
    return instance;
}

std::string
PlayerWebView::profile(const std::string &username, const std::string &firstName, const std::string &lastName,
                       const std::string &email, const int &wins, const int &games)
{
    std::string profile = R"({
        "username": ")" + username +
                          R"(","firstName": ")" + firstName + R"(","lastName": ")" + lastName + R"(","email": ")" +
                          email + R"(","wins": )" + std::to_string(wins) + R"(,"games": )" + std::to_string(games) +
                          R"(, "userType" : "player"})";
    return profile;
}

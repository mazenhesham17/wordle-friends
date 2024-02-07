#include "PlayerWebView.h"
#include <iostream>

PlayerWebView *PlayerWebView::instance = nullptr;

PlayerWebView *PlayerWebView::getInstance()
{
    if (instance == nullptr)
        instance = new PlayerWebView();
    return instance;
}

std::string PlayerWebView::profile(const std::string &username, const std::string &firstName, const std::string &lastName, const std::string &email)
{
    std::string profile = R"({
        "username": ")" + username +
                          R"(","firstName": ")" + firstName + R"(","lastName": ")" + lastName + R"(","email": ")" + email + R"(", "userType" : "player"})";
    return profile;
}

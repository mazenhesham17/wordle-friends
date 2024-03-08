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

std::string
PlayerWebView::friendView(const std::string &firstName, const std::string &lastName, const int &playerID)
{
    std::string friendView = R"({ "name": ")" + firstName + " " + lastName + R"(", "playerID": )" + std::to_string(playerID) +
                             R"(})";
    return friendView;
}

std::string
PlayerWebView::searchView(const std::string &firstName, const std::string &lastName,
                          const int &playerID, const bool &isFriend)
{
    std::string searchView = R"({ "name": ")" + firstName + " " + lastName + R"(", "playerID": )" + std::to_string(playerID) +
                             R"(, "isFriend": )" + std::to_string(isFriend) + R"(})";
    return searchView;
}

std::string
PlayerWebView::playersFriendView(const std::vector<std::pair<int, std::pair<std::string, std::string>>> &players)
{
    std::string playersView = R"({ "players": [)";
    for (auto &player : players)
    {
        playersView += friendView(player.second.first, player.second.second, player.first) + ",";
    }
    playersView.pop_back();
    playersView += "]}";
    return playersView;
}

std::string
PlayerWebView::playersSearchView(const std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string>>> &players)
{
    std::string playersView = R"({ "players": [)";
    for (auto &player : players)
    {
        playersView += searchView(player.second.first, player.second.second, player.first.first, player.first.second) + ",";
    }
    playersView.pop_back();
    playersView += "]}";
    return playersView;
}
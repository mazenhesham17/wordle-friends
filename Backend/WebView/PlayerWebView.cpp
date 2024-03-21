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
                       const std::string &email)
{
    std::string profile = R"({
        "username": ")" + username +
                          R"(","firstName": ")" + firstName + R"(","lastName": ")" + lastName + R"(","email": ")" +
                          email + R"(", "userType" : "player"})";
    return profile;
}

std::string
PlayerWebView::games(const std::vector<std::tuple<std::string, int, int>> &gamesDetails)
{
    std::string gamesView = R"({ "games": [)";
    for (auto &game : gamesDetails)
    {
        gamesView += R"({ "Date": ")" + std::get<0>(game) + R"(", "wins": )" + std::to_string(std::get<1>(game)) +
                     R"(, "loses": )" + std::to_string(std::get<2>(game)) + R"(},)";
    }
    if (!gamesDetails.empty())
    {
        gamesView.pop_back();
    }
    gamesView += "]}";
    return gamesView;
}

std::string
PlayerWebView::friendChatView(const std::string &firstName, const std::string &lastName, const std::string &lastMessage, const int &playerID)
{
    std::string friendView = R"({ "firstName": ")" + firstName + R"(", "lastName" : ")" + lastName + R"(", "lastMessage" : )" + lastMessage + R"(, "playerID": )" + std::to_string(playerID) +
                             R"(})";
    return friendView;
}

std::string
PlayerWebView::friendProfileView(const std::string &firstName, const std::string &lastName)
{
    std::string label;
    label += std::toupper(firstName[0]);
    label += std::toupper(lastName[0]);
    std::string friendView = R"({ "label": ")" + label + R"("})";
    return friendView;
}

std::string
PlayerWebView::searchView(const std::string &username, const std::string &firstName, const std::string &lastName,
                          const int &playerID, const bool &isFriend)
{
    std::string searchView = R"({ "firstName": ")" + firstName + R"(", "lastName" : ")" + lastName + R"(", "username": ")" + username + R"(", "playerID": )" + std::to_string(playerID) +
                             R"(, "isFriend": )" + std::to_string(isFriend) + R"(})";
    return searchView;
}

std::string
PlayerWebView::playersFriendProfileView(const std::vector<std::pair<std::string, std::string>> &friends)
{
    std::string playersView = R"({ "friends": [)";
    for (auto &player : friends)
    {
        playersView += friendProfileView(player.first, player.second) + ",";
    }
    if (!friends.empty())
    {
        playersView.pop_back();
    }
    playersView += "]}";
    return playersView;
}

std::string
PlayerWebView::playersSearchView(const std::vector<std::tuple<std::string, std::string, std::string, int, int>> &players)
{
    std::string playersView = R"({ "players": [)";
    for (auto &player : players)
    {
        playersView += searchView(std::get<0>(player), std::get<1>(player), std::get<2>(player), std::get<3>(player), std::get<4>(player)) + ",";
    }
    if (!players.empty())
    {
        playersView.pop_back();
    }
    playersView += "]}";
    return playersView;
}
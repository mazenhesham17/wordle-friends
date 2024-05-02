#include "AdminWebView.h"

AdminWebView *AdminWebView::instance = nullptr;

AdminWebView *AdminWebView::getInstance()
{
    if (instance == nullptr)
        instance = new AdminWebView();
    return instance;
}

std::string AdminWebView::gamesList(const std::vector<std::tuple<std::string, int, int>> &games)
{
    std::string gamesList = "[";
    for (auto &game : games)
    {
        gamesList += R"({ "Date": ")" + std::get<0>(game) + R"(", "wins": )" + std::to_string(std::get<1>(game)) +
                     R"(, "loses": )" + std::to_string(std::get<2>(game)) + R"(},)";
    }
    if (!games.empty())
        gamesList.pop_back();
    gamesList += "]";
    return gamesList;
}

std::string AdminWebView::messagesList(const std::vector<std::tuple<std::string, int>> &messages)
{
    std::string messagesList = "[";
    for (auto &message : messages)
    {
        messagesList += R"({ "Date": ")" + std::get<0>(message) + R"(", "count": )" + std::to_string(std::get<1>(message)) + R"(},)";
    }
    if (!messages.empty())
        messagesList.pop_back();
    messagesList += "]";
    return messagesList;
}

std::string AdminWebView::playersList(const std::vector<std::tuple<std::string, int>> &players)
{
    std::string playersList = "[";
    for (auto &player : players)
    {
        playersList += R"({ "Date": ")" + std::get<0>(player) + R"(", "count": )" + std::to_string(std::get<1>(player)) + R"(},)";
    }
    if (!players.empty())
        playersList.pop_back();
    playersList += "]";
    return playersList;
}

std::string AdminWebView::profile(const std::string &username, const std::string &email)
{
    std::string profile = R"({
        "username": ")" + username +
                          R"(","email": ")" + email + R"(", "userType" : "admin" })";
    return profile;
}

std::string AdminWebView::dashboard(const int &totalPlayers, const int &totalGames, const int &totalWins, const int &totalMessages,
                                    const std::vector<std::tuple<std::string, int, int>> &games, const std::vector<std::tuple<std::string, int>> &messages, const std::vector<std::tuple<std::string, int>> &players)
{
    std::string dashboard = R"({
        "totalPlayers": )" + std::to_string(totalPlayers) +
                            R"(,"totalGames": )" + std::to_string(totalGames) +
                            R"(,"totalWins": )" + std::to_string(totalWins) +
                            R"(,"totalMessages": )" + std::to_string(totalMessages) +
                            R"(,"games": )" + gamesList(games) +
                            R"(,"messages": )" + messagesList(messages) +
                            R"(,"players": )" + playersList(players) + R"(})";
    return dashboard;
}

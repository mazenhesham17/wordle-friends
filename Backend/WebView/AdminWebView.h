#ifndef BACKEND_ADMINWEBVIEW_H
#define BACKEND_ADMINWEBVIEW_H

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

class AdminWebView
{
    static AdminWebView *instance;

    AdminWebView(){};

    std::string gamesList(const std::vector<std::tuple<std::string, int, int>> &games);

    std::string messagesList(const std::vector<std::tuple<std::string, int>> &messages);

    std::string playersList(const std::vector<std::tuple<std::string, int>> &players);

public:
    static AdminWebView *getInstance();

    std::string profile(const std::string &username, const std::string &email);

    std::string dashboard(const int &totalPlayers, const int &totalGames, const int &totalWins, const int &totalMessages,
                          const std::vector<std::tuple<std::string, int, int>> &games, const std::vector<std::tuple<std::string, int>> &messages,
                          const std::vector<std::tuple<std::string, int>> &players);
};

#endif // BACKEND_ADMINWEBVIEW_H

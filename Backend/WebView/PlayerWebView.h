#ifndef BACKEND_PLAYERWEBVIEW_H
#define BACKEND_PLAYERWEBVIEW_H

#include <string>
#include <vector>
#include <tuple>

class PlayerWebView
{
    static PlayerWebView *instance;

    PlayerWebView(){};

public:
    static PlayerWebView *getInstance();

    std::string profile(const std::string &username, const std::string &firstName, const std::string &lastName,
                        const std::string &email);

    std::string games(const std::vector<std::tuple<std::string, int, int>> &gamesDetails);

    std::string friendProfileView(const std::string &firstName, const std::string &lastName);

    std::string friendChatView(const std::string &firstName, const std::string &lastName, const std::string &lastMessage, const int &playerID);

    std::string searchView(const std::string &username, const std::string &firstName, const std::string &lastName,
                           const int &playerID, const bool &isFriend);

    std::string playersFriendProfileView(const std::vector<std::pair<std::string, std::string>> &friends);

    std::string playersSearchView(const std::vector<std::tuple<std::string, std::string, std::string, int, int>> &players);

    std::string gameView(const std::string &firstName, const std::string &lastName, const std::string &username);
};

#endif // BACKEND_PLAYERWEBVIEW_H

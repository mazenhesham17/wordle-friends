#ifndef BACKEND_PLAYERWEBVIEW_H
#define BACKEND_PLAYERWEBVIEW_H

#include <string>
#include <vector>

class PlayerWebView
{
    static PlayerWebView *instance;

    PlayerWebView(){};

public:
    static PlayerWebView *getInstance();

    std::string profile(const std::string &username, const std::string &firstName, const std::string &lastName,
                        const std::string &email, const int &wins, const int &games);

    std::string friendView(const std::string &firstName, const std::string &lastName, const int &playerID);

    std::string searchView(const std::string &firstName, const std::string &lastName,
                           const int &playerID, const bool &isFriend);

    std::string playersFriendView(const std::vector<std::pair<int, std::pair<std::string, std::string>>> &players);

    std::string playersSearchView(const std::vector<std::pair<std::pair<int, int>, std::pair<std::string, std::string>>> &players);
};

#endif // BACKEND_PLAYERWEBVIEW_H

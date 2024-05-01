#ifndef BACKEND_PLAYERCONTROLLER_H
#define BACKEND_PLAYERCONTROLLER_H

#include <string>
#include <tuple>
#include <vector>
#include "BaseController.h"
#include "../Database/dml.h"
#include "../Database/dql.h"
#include "../Model/Player.h"
#include "../WebView/PlayerWebView.h"

class PlayerController : public BaseController
{

    static PlayerController *instance;

    PlayerWebView *playerWebView;

    PlayerController(){};

public:
    static PlayerController *getInstance();

    std::string profile(const User *user) override;

    std::string games(const int &playerID);

    std::string gameView(const int &playerID);

    std::string profileFriends(const int &playerID);

    std::string chatFriends(const int &playerID);

    std::string search(const int &playerID, const std::string &partialUsername);

    Player createPlayer(const User *user);

    bool addFriend(const int &playerID, const int &friendID);

    bool isFriend(const int &playerID, const int &friendID);

    bool isUserIDExist(const int &userID);

    bool updatePlayer(const int &playerID, const std::string &field, const std::string &value);
};

#endif // BACKEND_PLAYERCONTROLLER_H

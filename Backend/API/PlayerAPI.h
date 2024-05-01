#ifndef BACKEND_PLAYERAPI_H
#define BACKEND_PLAYERAPI_H

#include "../Controller/GameController.h"
#include "../Controller/PlayerController.h"
#include "../Controller/SocketController.h"
#include "../Controller/ResponseController.h"
#include "../Controller/RoomController.h"
#include "../Controller/UserController.h"
#include "../Model/Player.h"
#include "../Model/Response.h"

class PlayerAPI
{
    static PlayerAPI *instance;

    ResponseController *responseController;
    PlayerController *playerController;

    PlayerAPI();

public:
    static PlayerAPI *getInstance();

    Response profile(const User *player);

    Response addFriend(const int &playerID, const int &friendID);

    Response profileFriends(const int &playerID);

    Response chatFriends(const int &playerID);

    Response games(const int &playerID);

    Response search(const int &playerID, const std::string &paritialUsername);

    Response newGame(const std::string &word, const int &playerID, const std::string &type);

    Response updatePlayer(const int &playerID, const std::string &field, const std::string &value);
};

#endif // BACKEND_PLAYERAPI_H

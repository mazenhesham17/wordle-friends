#ifndef BACKEND_PLAYERAPI_H
#define BACKEND_PLAYERAPI_H

#include <boost/asio/ip/tcp.hpp>
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

    PlayerAPI() {}

public:
    static PlayerAPI *getInstance();

    Response profile(const User *player);

    Response newGame(const std::string &word, const int &playerID);

    Response updatePlayer(const int playerID, const std::string &field, const std::string &value);

    Response createRoom(const int &playerID, boost::asio::io_context &ioContext);

    Response joinRoom(const std::string &roomID, boost::asio::io_context &ioContext);
};

#endif // BACKEND_PLAYERAPI_H

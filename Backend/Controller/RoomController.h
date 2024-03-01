#ifndef BACKEND_ROOMCONTROLLER_H
#define BACKEND_ROOMCONTROLLER_H

#include <string>
#include <vector>
#include <boost/asio/ip/tcp.hpp>
#include "../Database/dql.h"
#include "../Model/Room.h"
#include "../Model/RoomContainer.h"
#include "../WebView/RoomWebView.h"
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class RoomController
{
    static RoomController *instance;

    RoomController(){};

    RoomContainer roomContainer;

public:
    static RoomController *getInstance();

    std::string createGameRoom(const int &playerID, const int &gameID, const std::string &type);

    std::string createChatRoom(int playerID, int friendID);

    void addSocketToRoom(Room &room, int &playerID, tcp::socket &socket);

    bool isRoomExist(const std::string &roomID);

    std::vector<int> &getPlayerIDs(Room &room);

    std::vector<tcp::socket> &getSockets(Room &room);

    Room &getRoom(const std::string &roomID);
};

#endif // BACKEND_ROOMCONTROLLER_H

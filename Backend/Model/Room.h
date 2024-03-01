#ifndef BACKEND_ROOM_H
#define BACKEND_ROOM_H

#include <string>
#include <unordered_set>
#include <vector>
#include <utility>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "../Controller/SocketController.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class Room
{
    std::string roomID;

    std::vector<int> playerIDs;

    std::vector<tcp::socket> sockets;

public:
    Room(std::string roomID);

    Room(Room &&other) noexcept;

    std::string getRoomID() const;

    void setRoomID(const std::string &roomID);

    std::vector<int> &getPlayerIDs();

    std::vector<tcp::socket> &getSockets();

    void addSocket(const int playerID, tcp::socket &socket);

    ~Room();
};

#endif // BACKEND_ROOM_H

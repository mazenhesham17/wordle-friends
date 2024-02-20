#ifndef BACKEND_SOCKETCONTROLLER_H
#define BACKEND_SOCKETCONTROLLER_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include "GameController.h"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class SocketController
{
    static SocketController *instance;
    GameController *gameController;
    net::io_context ioc{1};
    tcp::acceptor acceptor{ioc};
    SocketController();

public:
    static SocketController *getInstance();
    void start(int playerID);
    void singleGameSession(tcp::socket socket, int playerID);
};

#endif // BACKEND_SOCKETCONTROLLER_H

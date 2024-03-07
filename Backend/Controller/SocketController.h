#ifndef BACKEND_SOCKETCONTROLLER_H
#define BACKEND_SOCKETCONTROLLER_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
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
    net::io_context ioc{static_cast<int>(std::thread::hardware_concurrency())};

    SocketController(){};

public:
    static SocketController *getInstance();

    void connectSocket(tcp::socket &socket);

    void waitForAsyncOperations();

    net::io_context &getIOContext();
};

#endif // BACKEND_SOCKETCONTROLLER_H

#ifndef BACKEND_SESSION_H
#define BACKEND_SESSION_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class GameController;

class RoomController;

class SocketController;

class Session : public std::enable_shared_from_this<Session>
{
protected:
    GameController *gameController;
    RoomController *roomController;

    beast::flat_buffer buffer;
    websocket::stream<beast::tcp_stream> ws;
    std::mutex writeMutex;
    std::mutex readMutex;

    int playerID;

    void accept();

public:
    Session(tcp::socket &&socket, int playerID);

    int getPlayerID();

    virtual void onRead(beast::error_code ec, std::size_t bytes_transferred);

    virtual void onWrite(beast::error_code ec, std::size_t bytes_transferred);

    void send(const std::string &message);

    void asyncSend(const std::string &message);

    std::string receive();

    void asyncReceive();

    bool isConnected();

    void close();

    virtual void launchSession(const std::string &roomID) = 0;

    virtual bool isFinished() = 0;

    virtual ~Session();
};

#endif // BACKEND_SESSION_H

#include "Session.h"
#include "../Controller/GameController.h"
#include "../Controller/RoomController.h"

Session::Session(tcp::socket &&socket, int playerID)
    : ws(std::move(socket))
{
    gameController = GameController::getInstance();
    roomController = RoomController::getInstance();
    this->playerID = playerID;
}

void Session::accept()
{
    ws.accept();
}

void Session::onRead(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (ec && ec != websocket::error::closed)
    {
        std::cerr << "Error: " << ec.message() << std::endl;
        return;
    }
}

void Session::onWrite(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (ec && ec != websocket::error::closed)
    {
        std::cerr << "Error: " << ec.message() << std::endl;
        return;
    }
}

void Session::send(const std::string &message)
{
    ws.write(net::buffer(message));
}

void Session::asyncSend(const std::string &message)
{
    // lock to ensure that only one thread writes at a time
    std::lock_guard<std::mutex> lock(writeMutex);

    ws.async_write(net::buffer(message),
                   beast::bind_front_handler(&Session::onWrite, shared_from_this()));
}

std::string Session::receive()
{
    buffer.consume(buffer.size());
    ws.read(buffer);
    return beast::buffers_to_string(buffer.data());
}

void Session::asyncReceive()
{
    // lock to ensure that only one thread reads at a time
    std::lock_guard<std::mutex> lock(readMutex);
    buffer.consume(buffer.size());
    ws.async_read(buffer, beast::bind_front_handler(&Session::onRead, shared_from_this()));
}

bool Session::isConnected()
{
    return ws.is_open();
}

void Session::close()
{
    ws.close(websocket::close_code::normal);
}

int Session::getPlayerID()
{
    return playerID;
}

Session::~Session()
{
    close();
    std::cout << "Session ended" << std::endl;
}
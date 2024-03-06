#include "SocketController.h"

SocketController *SocketController::instance = nullptr;

SocketController *SocketController::getInstance()
{
    if (instance == nullptr)
    {
        instance = new SocketController();
    }
    return instance;
}

net::io_context &SocketController::getIOContext()
{
    return ioc;
}

void SocketController::connectSocket(tcp::socket &socket)
{
    try
    {
        auto const address = net::ip::make_address("127.0.0.1");
        auto const port = static_cast<unsigned short>(8080);
        tcp::acceptor acceptor{ioc, {address, port}};
        acceptor.accept(socket);
    }
    catch (beast::system_error const &se)
    {
        // This indicates that the session was closed
        if (se.code() != websocket::error::closed)
        {
            std::cerr << "Error: " << se.code().message() << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void SocketController::waitForAsyncOperations()
{
    ioc.restart();
    ioc.run();
}
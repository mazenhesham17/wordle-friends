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
        std::string backend_url = std::getenv("BACKEND_URL");
        tcp::resolver resolver{ioc};
        tcp::endpoint endpoint = *resolver.resolve(backend_url, "8080").begin();
        // auto const address = net::ip::make_address(backend_url);
        // auto const port = static_cast<unsigned short>(8080);
        std::cout << "Connecting to " << endpoint << std::endl;
        tcp::acceptor acceptor{ioc, endpoint};
        acceptor.accept(socket);
    }
    catch (beast::system_error const &se)
    {
        // This indicates that the session was closed
        if (se.code() != websocket::error::closed)
        {
            std::cerr << "Beast error: " << se.code().message() << std::endl;
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception error: " << e.what() << std::endl;
    }
}

void SocketController::waitForAsyncOperations()
{
    ioc.restart();
    ioc.run();
}
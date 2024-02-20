#include "SocketController.h"

SocketController *SocketController::instance = nullptr;

SocketController::SocketController()
{
    gameController = GameController::getInstance();
    auto const address = net::ip::make_address("127.0.0.1");
    auto const port = static_cast<unsigned short>(std::atoi("8080"));

    acceptor = tcp::acceptor{ioc, {address, port}};
};

void SocketController::singleGameSession(tcp::socket socket)
{
    try
    {
        // Construct the stream by moving in the socket
        websocket::stream<tcp::socket> ws{std::move(socket)};

        // Set a decorator to change the Server of the handshake
        ws.set_option(websocket::stream_base::decorator(
            [](websocket::response_type &res)
            {
                res.set(http::field::server,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                            "websocket-server-sync");
            }));

        // Accept the websocket handshake
        ws.accept();

        beast::flat_buffer buffer;

        ws.read(buffer);

        int gameId = std::stoi(beast::buffers_to_string(buffer.data()));

        gameController->startGame(gameId);

        ws.write(net::buffer("Game started!"));

        for (int i = 0; i < 6; i++)
        {
            beast::flat_buffer word_buffer;
            ws.read(word_buffer);
            std::string message = beast::buffers_to_string(word_buffer.data());
            std::string result = gameController->submitGuess(message, gameId);
            ws.write(net::buffer(result));
        }

        ws.write(net::buffer("You lose!"));
    }
    catch (beast::system_error const &se)
    {
        // This indicates that the session was closed
        if (se.code() != websocket::error::closed)
            std::cerr << "Error: " << se.code().message() << std::endl;
    }
    catch (std::exception const &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void SocketController::start()
{
    try
    {
        while (true)
        {
            // This will receive the new connection
            tcp::socket socket{ioc};

            // Block until we get a connection
            acceptor.accept(socket);

            // Launch the session, transferring ownership of the socket
            std::thread(
                &SocketController::singleGameSession,
                this,
                std::move(socket))
                .detach();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

SocketController *SocketController::getInstance()
{
    if (instance == nullptr)
    {
        instance = new SocketController();
    }
    return instance;
}
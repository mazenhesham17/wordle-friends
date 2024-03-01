#include "SingleGameSession.h"

void SingleGameSession::launchSession(Room &room)
{
    int gameId = 0;
    int playerID = roomController->getPlayerIDs(room).back();
    tcp::socket &socket = roomController->getSockets(room).back();
    try
    {
        websocket::stream<tcp::socket> ws{std::move(socket)};

        ws.accept();

        ws.text(true);

        beast::flat_buffer buffer;

        ws.read(buffer);

        gameId = std::stoi(beast::buffers_to_string(buffer.data()));

        gameController->startGame(gameId);

        ws.write(net::buffer("Game started!"));

        bool flag = false;

        for (int i = 0; i < 6; i++)
        {
            buffer.consume(buffer.size());
            ws.read(buffer);
            std::string message = beast::buffers_to_string(buffer.data());
            std::string result = gameController->submitGuess(message, gameId);
            ws.write(net::buffer(result));
            if (gameController->match(message, gameId))
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            ws.write(net::buffer("You win!"));
            gameController->winGame(gameId, playerID);
            ws.close(websocket::close_code::normal);
            std::cout << "Socket closed " << ws.is_open() << std::endl;
        }
        else
        {
            ws.write(net::buffer("You lose!"));
            gameController->endGame(gameId);
            ws.close(websocket::close_code::normal);
        }
    }
    catch (beast::system_error const &se)
    {
        gameController->endGame(gameId);
        // This indicates that the session was closed
        if (se.code() != websocket::error::closed)
        {
            std::cerr << "Error: " << se.code().message() << std::endl;
        }
    }
    catch (std::exception const &e)
    {
        gameController->endGame(gameId);
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

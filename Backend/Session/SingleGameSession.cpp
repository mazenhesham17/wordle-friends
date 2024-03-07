#include "SingleGameSession.h"
#include "../Controller/GameController.h"
#include "../Controller/RoomController.h"

SingleGameSession::SingleGameSession(tcp::socket &&socket, std::string roomID, int playerID)
    : GameSession(std::move(socket), roomID, playerID)
{
}

void SingleGameSession::launchSession()
{
    try
    {
        accept();

        gameID = std::stoi(receive());

        gameController->joinGame(gameID, playerID);

        gameController->startGame(gameID);

        send("Game started!");

        bool flag = false;

        while (turnsLeft)
        {
            std::string message = receive();

            std::string result = gameController->submitGuess(message, gameID);

            send(result);

            if (gameController->match(message, gameID))
            {
                flag = true;
                break;
            }
            turnsLeft--;
        }
        std::cout << "Turns : " << turnsLeft << std::endl;
        if (flag)
        {
            send("You win!");
            gameController->winGame(gameID, playerID);
        }
        else
        {
            send("You lose!");
            gameController->endGame(gameID);
        }
        roomController->closeRoom(roomID);
        close();
    }
    catch (beast::system_error const &se)
    {
        gameController->endGame(gameID);
        roomController->closeRoom(roomID);
        // This indicates that the session was closed
        if (se.code() != websocket::error::closed)
        {
            std::cerr << "Beast error: " << se.code().message() << std::endl;
        }
    }
    catch (std::exception const &e)
    {
        gameController->endGame(gameID);
        roomController->closeRoom(roomID);
        std::cerr << "Exception error: " << e.what() << std::endl;
    }
}

bool SingleGameSession::isFinished()
{
    return false;
}

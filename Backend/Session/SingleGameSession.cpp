#include "SingleGameSession.h"
#include "../Controller/GameController.h"

SingleGameSession::SingleGameSession(tcp::socket &&socket, int playerID)
    : Session(std::move(socket), playerID)
{
}

void SingleGameSession::launchSession(const std::string &roomID)
{
    try
    {
        accept();

        gameID = std::stoi(receive());

        gameController->joinGame(gameID, playerID);

        gameController->startGame(gameID);

        send("Game started!");

        bool flag = false;

        for (int i = 0; i < 6; i++)
        {
            std::string message = receive();

            std::string result = gameController->submitGuess(message, gameID);

            send(result);

            if (gameController->match(message, gameID))
            {
                flag = true;
                break;
            }
        }
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
        close();
    }
    catch (beast::system_error const &se)
    {
        gameController->endGame(gameID);
        // This indicates that the session was closed
        if (se.code() != websocket::error::closed)
        {
            std::cerr << "Beast error: " << se.code().message() << std::endl;
        }
    }
    catch (std::exception const &e)
    {
        gameController->endGame(gameID);
        std::cerr << "Exception error: " << e.what() << std::endl;
    }
}

bool SingleGameSession::isFinished()
{
    return false;
}

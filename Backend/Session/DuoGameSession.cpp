#include "DuoGameSession.h"
#include "../Controller/GameController.h"
#include "../Controller/RoomController.h"
#include "../Controller/SocketController.h"

DuoGameSession::DuoGameSession(tcp::socket &&socket, std::string roomID, int playerID)
    : Session(std::move(socket), playerID), roomID(std::move(roomID))
{
}

void DuoGameSession::onRead(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (ec)
    {
        if (roomController->getConnectedSessionsCount(roomID) == 0)
        {
            // both users are disconnected
            gameController->endGame(gameID);
        }
        if (ec != websocket::error::closed && ec != net::error::not_connected)
        {
            std::cerr << "OnRead error: " << ec.message() << std::endl;
        }
        return;
    }

    if (turnsLeft == 0)
    {
        send("You lose!");
        if (roomController->getFinishedSessionsCount(roomID) == 2)
        {
            gameController->endGame(gameID);
            roomController->endAllSessions(roomID);
        }
        return;
    }

    std::string message = beast::buffers_to_string(buffer.data());

    std::string result = gameController->submitGuess(message, gameID);

    asyncSend(result);

    std::string currentTemplate = result.substr(result.find(':') + 2);

    std::string opponentResult = gameController->mergeTemplates(currentTemplate, oldTemplate);

    // broadcast to the other user
    roomController->broadcast(opponentResult, roomID, playerID);

    if (gameController->match(message, gameID))
    {
        send("You win!");
        gameController->winGame(gameID, playerID);
        // broadcast to the other user
        roomController->broadcast("You lose!", roomID, playerID);
        roomController->endAllSessions(roomID);
        return;
    }

    oldTemplate = opponentResult.substr(opponentResult.find(':') + 2);

    turnsLeft--;

    asyncReceive();
}

void DuoGameSession::onWrite(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);
    if (roomController->getConnectedSessionsCount(roomID) == 0)
    {
        // both users are disconnected
        gameController->endGame(gameID);
    }
    if (ec)
    {
        if (ec != websocket::error::closed && ec != net::error::not_connected)
        {
            std::cerr << "OnWrite error: " << ec.message() << std::endl;
        }
        return;
    }
}

void DuoGameSession::launchSession(const std::string &roomID)
{
    try
    {
        accept();

        gameID = std::stoi(receive());

        // wait until the other user joins

        roomController->blockRoom(roomID);

        if (roomController->getConnectedSessionsCount(roomID) != 2)
        {
            send("Time out!");
            gameController->deleteGame(gameID);
            roomController->endAllSessions(roomID);
            return;
        }

        gameController->joinGame(gameID, playerID);
        gameController->startGame(gameID);

        send("Game started!");

        asyncReceive();

        SocketController::getInstance()->waitForAsyncOperations();
    }
    catch (beast::system_error const &se)
    {
        if (se.code() != websocket::error::closed)
        {
            std::cerr << "Beast error: " << se.code().message() << std::endl;
        }
    }
    catch (std::exception const &e)
    {
        std::cerr << "Exception Eeror: " << e.what() << std::endl;
    }
}

bool DuoGameSession::isFinished()
{
    return turnsLeft == 0;
}

#include "ChatSession.h"
#include "../Controller/RoomController.h"
#include "../Controller/SocketController.h"
#include "../Controller/ChatController.h"

ChatSession::ChatSession(tcp::socket &&socket, const std::string &roomId, int playerId)
    : Session(std::move(socket), roomId, playerId)
{
    chatController = ChatController::getInstance();
    chatID = chatController->getChatID(roomID);
}

void ChatSession::onRead(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (ec)
    {
        if (ec != websocket::error::closed)
        {
            std::cerr << "OnRead error: " << ec.message() << std::endl;
        }
        return;
    }

    std::string message = beast::buffers_to_string(buffer.data());

    if (message == "$M$W%B%")
    {
        // seen message
        chatController->readChat(chatID, playerID);
    }
    else
    {

        std::string messageView = chatController->addMessage(playerID, chatID, message);

        roomController->chatBroadcast(messageView, roomID, playerID);
        roomController->chatNotify(chatID, playerID);
    }

    asyncReceive();
}

void ChatSession::launchSession()
{
    try
    {
        accept();

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
        std::cerr << "Exception error: " << e.what() << std::endl;
    }
}

bool ChatSession::isFinished()
{
    return false;
}

#include "PlayerAPI.h"

PlayerAPI *PlayerAPI::instance = nullptr;

PlayerAPI *PlayerAPI::getInstance()
{
    if (instance == nullptr)
    {
        instance = new PlayerAPI();
    }
    return instance;
}

Response PlayerAPI::profile(const User *player)
{
    Response response;
    ResponseController *responseController = ResponseController::getInstance();
    responseController->setSuccess(response, PlayerController::getInstance()->profile(player));
    return response;
}

Response PlayerAPI::newGame(const std::string &word, const int &playerID)
{
    Response response;
    ResponseController *responseController = ResponseController::getInstance();
    int gameID = GameController::getInstance()->newGame(word, playerID);
    responseController->setSuccess(response, RoomController::getInstance()->createGameRoom(playerID, gameID, "S"));
    return response;
}

Response PlayerAPI::updatePlayer(const int playerID, const std::string &field, const std::string &value)
{
    Response response;
    ResponseController *responseController = ResponseController::getInstance();
    if (PlayerController::getInstance()->updatePlayer(playerID, field, value))
    {
        User *user = new Player(UserController::getInstance()->retriveUserFromDB(playerID));
        return profile(user);
    }
    else
    {
        responseController->setFailure(response, "Player update failed");
    }
    return response;
}

// Response PlayerAPI::createRoom(const int &playerID, boost::asio::io_context &ioContext)
// {
//     Response response;
//     ResponseController *responseController = ResponseController::getInstance();
//     std::string roomID = RoomController::getInstance()->createRoom(playerID, ioContext);
//     responseController->setSuccess(response, R"({"roomID": ")" + roomID + R"("})" );
//     return response;
// }

// Response PlayerAPI::joinRoom(const std::string &roomID, boost::asio::io_context &ioContext)
// {
//     Response response;
//     ResponseController *responseController = ResponseController::getInstance();
//     if (RoomController::getInstance()->isRoomExist(roomID, ioContext))
//     {
//         Room room = RoomController::getInstance()->getRoom(roomID, ioContext);
//         boost::asio::ip::tcp::socket &socket = RoomController::getInstance()->getSocket(room);
//         SocketController::getInstance()->joinMultiplayerGameSession(std::move(socket));
//         responseController->setSuccess(response, R"({"message": "success"})");
//     }
//     else
//     {
//         responseController->setFailure(response, "Room does not exist");
//     }
//     return response;
// }
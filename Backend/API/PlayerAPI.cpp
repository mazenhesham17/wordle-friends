#include "PlayerAPI.h"

PlayerAPI *PlayerAPI::instance = nullptr;

PlayerAPI::PlayerAPI()
{
    responseController = ResponseController::getInstance();
    playerController = PlayerController::getInstance();
}

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
    responseController->setSuccess(response, playerController->profile(player));
    return response;
}

Response PlayerAPI::newGame(const std::string &word, const int &playerID, const std::string &type)
{
    Response response;
    int gameID = GameController::getInstance()->newGame(word);
    responseController->setSuccess(response, RoomController::getInstance()->createGameRoom(playerID, gameID, type));
    return response;
}

Response PlayerAPI::updatePlayer(const int &playerID, const std::string &field, const std::string &value)
{
    Response response;
    if (playerController->updatePlayer(playerID, field, value))
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

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

Response PlayerAPI::newGame(const std::string &word, const int &playerID, const std::string &type)
{
    Response response;
    ResponseController *responseController = ResponseController::getInstance();
    int gameID = GameController::getInstance()->newGame(word);
    responseController->setSuccess(response, RoomController::getInstance()->createGameRoom(playerID, gameID, type));
    return response;
}

Response PlayerAPI::updatePlayer(const int &playerID, const std::string &field, const std::string &value)
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

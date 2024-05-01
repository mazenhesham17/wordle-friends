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

Response PlayerAPI::addFriend(const int &playerID, const int &friendID)
{
    Response response;
    if (playerController->addFriend(playerID, friendID))
    {
        responseController->setSuccess(response, responseController->success());
    }
    else
    {
        responseController->setFailure(response, "Friend add failed");
    }
    return response;
}

Response PlayerAPI::chatFriends(const int &playerID)
{
    Response response;
    responseController->setSuccess(response, playerController->chatFriends(playerID));
    return response;
}

Response PlayerAPI::profileFriends(const int &playerID)
{
    Response response;
    responseController->setSuccess(response, playerController->profileFriends(playerID));
    return response;
}

Response PlayerAPI::games(const int &playerID)
{
    Response response;
    responseController->setSuccess(response, playerController->games(playerID));
    return response;
}

Response PlayerAPI::search(const int &playerID, const std::string &paritialUsername)
{
    Response response;
    responseController->setSuccess(response, playerController->search(playerID, paritialUsername));
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
        User *user = new Player(UserController::getInstance()->retrieveUserFromDB(playerID));
        return profile(user);
    }
    else
    {
        responseController->setFailure(response, "Player update failed");
    }
    return response;
}

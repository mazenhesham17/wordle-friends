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

Response PlayerAPI::newSingleGame(const std::string &word, const int &playerID)
{
    Response response;
    ResponseController *responseController = ResponseController::getInstance();
    responseController->setSuccess(response, GameController::getInstance()->newSinglePlayerGame(word, playerID));
    return response;
}
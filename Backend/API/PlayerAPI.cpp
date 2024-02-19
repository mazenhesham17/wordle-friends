#include "PlayerAPI.h"
#include "../Controller/ResponseController.h"
#include "../Controller/PlayerController.h"

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
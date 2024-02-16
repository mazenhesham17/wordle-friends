#include "PlayerController.h"
#include "../WebView/PlayerWebView.h"

PlayerController *PlayerController::instance = nullptr;

PlayerController *PlayerController::getInstance()
{
    if (instance == nullptr)
    {
        instance = new PlayerController();
    }
    return instance;
}

std::string PlayerController::profile(const Player &player)
{
    return PlayerWebView::getInstance()->profile(player.getUsername(), player.getFirstName(), player.getLastName(),
                                                 player.getEmail());
}
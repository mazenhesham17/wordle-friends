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

std::string PlayerController::profile(const User *user)
{
     return PlayerWebView::getInstance()->profile(user->getUsername(), user->getFirstName(), user->getLastName(),
                                                 user->getEmail());
}
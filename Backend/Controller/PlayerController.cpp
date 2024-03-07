#include "PlayerController.h"

PlayerController *PlayerController::instance = nullptr;

PlayerController *PlayerController::getInstance()
{
    if (instance == nullptr)
    {
        instance = new PlayerController();
    }
    return instance;
}

Player PlayerController::createPlayer(const User *user)
{
    Player player(*user);
    player.setWins(getWinsCountByUserID(user->getUserID()));
    player.setGames(getGamesCountByUserID(user->getUserID()));
    return player;
}

std::string PlayerController::profile(const User *user)
{
    Player player = createPlayer(user);
    return PlayerWebView::getInstance()->profile(player.getUsername(), player.getFirstName(), player.getLastName(),
                                                 player.getEmail(), player.getWins(), player.getGames());
}

bool PlayerController::updatePlayer(const int &playerID, const std::string &field, const std::string &value)
{
    return updatePlayerField(playerID, field.c_str(), value.c_str());
}
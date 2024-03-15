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
    return playerWebView->profile(player.getUsername(), player.getFirstName(), player.getLastName(),
                                  player.getEmail(), player.getWins(), player.getGames());
}

bool PlayerController::addFriend(const int &playerID, const int &friendID)
{
    return dbAddFriend(playerID, friendID);
}

bool PlayerController::isUserIDExist(const int &userID)
{
    return isUserExist(userID);
}

bool PlayerController::isFriend(const int &playerID, const int &friendID)
{
    return dbIsFriend(playerID, friendID);
}

bool PlayerController::updatePlayer(const int &playerID, const std::string &field, const std::string &value)
{
    return updatePlayerField(playerID, field.c_str(), value.c_str());
}

std::string PlayerController::friendView(const int &playerID)
{
    return playerWebView->friendView(getFirstNameByUserID(playerID), getLastNameByUserID(playerID), playerID);
}

std::string PlayerController::friends(const int &playerID)
{
    auto friends = getFriendListByUserID(playerID);
    std::vector<std::pair<int, std::pair<std::string, std::string>>> players;
    for (auto &friendID : friends)
    {
        players.push_back(std::make_pair(friendID, std::make_pair(getFirstNameByUserID(friendID), getLastNameByUserID(friendID))));
    }
    return playerWebView->playersFriendView(players);
}

std::string PlayerController::search(const int &playerID, const std::string &partialUsername)
{
    auto playersID = getPlayersListByPartialUsername(partialUsername);
    std::vector<std::tuple<std::string, std::string, std::string, int, int>> players;
    for (auto &friendID : playersID)
    {
        if (friendID == playerID)
            continue;
        players.emplace_back(getUsernameByUserID(friendID), getFirstNameByUserID(friendID), getLastNameByUserID(friendID), friendID, isFriend(playerID, friendID));
    }
    return playerWebView->playersSearchView(players);
}
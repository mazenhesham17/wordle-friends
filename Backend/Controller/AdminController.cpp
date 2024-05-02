#include "AdminController.h"

AdminController *AdminController::instance = nullptr;

AdminController *AdminController::getInstance()
{
    if (instance == nullptr)
    {
        instance = new AdminController();
    }
    return instance;
}

int AdminController::getMessageCount(const std::vector<std::tuple<std::string, int>> &messages)
{
    int cnt = 0;
    for (auto message : messages)
    {
        cnt += std::get<1>(message);
    }
    return cnt;
}

Admin AdminController::createAdmin(const User *user)
{
    Admin admin(*user);
    admin.setUserCounts(getTotalPlayersCount());
    admin.setWins(getTotalWinsCount());
    admin.setGames(getTotalGamesCount());
    return admin;
}

std::string AdminController::profile(const User *user)
{
    Admin admin = createAdmin(user);
    return AdminWebView::getInstance()->profile(user->getUsername(), user->getEmail());
}

std::string AdminController::dashboard(const Admin &admin, const int &offset)
{
    auto games = getAllGames(offset);
    auto messages = getAllMessages(offset);
    auto players = getAllPlayers(offset);
    auto messageCount = getMessageCount(messages);

    return AdminWebView::getInstance()->dashboard(admin.getUserCounts(), admin.getGames(), admin.getWins(), messageCount, games, messages, players);
}
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

std::string AdminController::dashboard(const Admin &admin)
{
    return AdminWebView::getInstance()->dashboard(admin.getUserCounts(), admin.getGames(), admin.getWins());
}
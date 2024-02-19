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

std::string AdminController::profile(const User *user)
{
    return AdminWebView::getInstance()->profile(user->getUsername(), user->getEmail());
}
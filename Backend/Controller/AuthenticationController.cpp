#include "AuthenticationController.h"

AuthenticationController *AuthenticationController::instance = nullptr;

AuthenticationController::AuthenticationController()
{
    tokenController = TokenController::getInstance();
}

AuthenticationController *AuthenticationController::getInstance()
{
    if (instance == nullptr)
        instance = new AuthenticationController();
    return instance;
}

bool AuthenticationController::isAuthenticatedUser(const std::string &token)
{
    return tokenController->verifyToken(token);
}

bool AuthenticationController::isAuthenticatedAdmin(const std::string &token)
{
    return tokenController->verifyToken(token) && tokenController->isUserAdmin(token);
}

bool AuthenticationController::isAuthenticatedPlayer(const std::string &token)
{
    return tokenController->verifyToken(token) && tokenController->isUserPlayer(token);
}


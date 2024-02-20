#include "AdminAPI.h"

AdminAPI *AdminAPI::instance = nullptr;

AdminAPI *AdminAPI::getInstance()
{
    if (instance == nullptr)
    {
        instance = new AdminAPI();
    }
    return instance;
}

Response AdminAPI::profile(const User *admin)
{
    Response response;
    ResponseController *responseController = ResponseController::getInstance();
    responseController->setSuccess(response, AdminController::getInstance()->profile(admin));
    return response;
}
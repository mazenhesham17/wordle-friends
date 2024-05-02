#include "AdminAPI.h"

AdminAPI *AdminAPI::instance = nullptr;

AdminAPI::AdminAPI()
{
    responseController = ResponseController::getInstance();
}

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
    responseController->setSuccess(response, AdminController::getInstance()->profile(admin));
    return response;
}

Response AdminAPI::dashboard(const Admin &admin, const int &offset)
{
    Response response;
    responseController->setSuccess(response, AdminController::getInstance()->dashboard(admin, offset));
    return response;
}
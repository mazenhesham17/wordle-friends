#include "AdminAPI.h"
#include "../WebView/AdminWebView.h"
#include "../Controller/AdminController.h"
#include "../Controller/ResponseController.h"
#include <iostream>

AdminAPI *AdminAPI::instance = nullptr;

AdminAPI *AdminAPI::getInstance()
{
    if (instance == nullptr)
    {
        instance = new AdminAPI();
    }
    return instance;
}

Response AdminAPI::profile(const Admin &admin)
{
    Response response;
    ResponseController *responseController = ResponseController::getInstance();
    responseController->setSuccess(response, AdminController::getInstance()->profile(admin));
    return response;
}
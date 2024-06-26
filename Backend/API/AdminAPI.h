#ifndef BACKEND_ADMINAPI_H
#define BACKEND_ADMINAPI_H

#include <iostream>
#include "../Controller/AdminController.h"
#include "../Controller/ResponseController.h"
#include "../Model/Response.h"
#include "../Model/User.h"
#include "../WebView/AdminWebView.h"

class AdminAPI
{
    static AdminAPI *instance;

    ResponseController *responseController;

    AdminAPI();

public:
    static AdminAPI *getInstance();

    Response profile(const User *admin);

    Response dashboard(const Admin &admin, const int &offset);
};

#endif // BACKEND_ADMINAPI_H

#ifndef BACKEND_USERAPI_H
#define BACKEND_USERAPI_H

#include <regex>
#include "../Database/dml.h"
#include "../Database/dql.h"
#include "../Controller/ResponseController.h"
#include "../Controller/TokenController.h"
#include "../Controller/UserController.h"
#include "../Model/Response.h"
#include "../Model/User.h"
#include "../WebView/AdminWebView.h"
#include "../WebView/PlayerWebView.h"
#include "../WebView/TokenWebView.h"

class UserAPI
{
    static UserAPI *instance;
    ResponseController *responseController;
    UserController *userController;
    UserAPI();

public:
    static UserAPI *getInstance();

    Response login(const std::string &identifier, const std::string &password);

    Response registerUser(const User &user);

    Response info(const int &userType);
};

#endif // BACKEND_USERAPI_H

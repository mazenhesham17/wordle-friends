#ifndef BACKEND_USERAPI_H
#define BACKEND_USERAPI_H

#include <jsoncons/json.hpp>
#include <jwt-cpp/jwt.h>
#include "../Database/constants.h"
#include "../Database/dml.h"
#include "../Database/dql.h"
#include "../Controller/ResponseController.h"
#include "../Controller/TokenController.h"
#include "../Controller/UserController.h"
#include "../Model/Response.h"
#include "../Model/User.h"
#include "../WebView/AdminWebView.h"
#include "../WebView/PlayerWebView.h"
#include "../WebView/GameWebView.h"
#include "../WebView/TokenWebView.h"

class UserAPI
{
    static UserAPI *instance;

    UserAPI() {}

public:
    static UserAPI *getInstance();

    Response login(const std::string &identifier, const std::string &password);

    Response registerUser(const User &user);

    Response newSingleGame(const std::string &token, const std::string &game);
};

#endif // BACKEND_USERAPI_H

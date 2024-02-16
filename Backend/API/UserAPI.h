#ifndef BACKEND_USERAPI_H
#define BACKEND_USERAPI_H

#include "../Model/Response.h"
#include "../Model/User.h"
#include "../Controller/ResponseController.h"

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

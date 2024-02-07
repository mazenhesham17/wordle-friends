#ifndef BACKEND_USERAPI_H
#define BACKEND_USERAPI_H
#include "../Model/Response.h"
#include "../Controller/ResponseController.h"

class UserAPI
{
    static UserAPI *instance;
    UserAPI() {}

public:
    static UserAPI *getInstance();

    Response login(const std::string &identifier, const std::string &password);
    Response registerUser(const std::string &username, const std::string &firstName, const std::string &lastName, const std::string &email, const std::string &password);
    Response profile(const std::string &token);
};

#endif // BACKEND_USERAPI_H

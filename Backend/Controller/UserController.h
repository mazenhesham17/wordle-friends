#ifndef BACKEND_USERCONTROLLER_H
#define BACKEND_USERCONTROLLER_H

#include "../Model/User.h"
#include <jsoncons/json.hpp>

class UserController
{
    static UserController *instance;

    UserController(){};

public:
    static UserController *getInstance();

    User createUser(const jsoncons::json &json);

    User retriveUserFromDB(const int &userID);

    int addUser(const User &user);

    std::string successfulAddition(const int &userID);
};

#endif // BACKEND_USERCONTROLLER_H

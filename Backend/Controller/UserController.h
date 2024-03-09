#ifndef BACKEND_USERCONTROLLER_H
#define BACKEND_USERCONTROLLER_H

#include <jsoncons/json.hpp>
#include "../Database/dml.h"
#include "../Database/dql.h"
#include "../Model/User.h"

class UserController
{
    static UserController *instance;

    UserController(){};

public:
    static UserController *getInstance();

    User createUser(const jsoncons::json &json);

    User retrieveUserFromDB(const int &userID);

    int addUser(const User &user);

    std::string successfulAddition(const int &userID);
};

#endif // BACKEND_USERCONTROLLER_H

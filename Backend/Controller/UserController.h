#ifndef BACKEND_USERCONTROLLER_H
#define BACKEND_USERCONTROLLER_H

#include <nlohmann/json.hpp>
#include "../Database/dml.h"
#include "../Database/dql.h"
#include "../Model/User.h"
#include "../WebView/UserWebView.h"

class UserController
{
    static UserController *instance;

    UserController(){};

public:
    static UserController *getInstance();

    User createUser(const nlohmann::json &json);

    User retrieveUserFromDB(const int &userID);

    std::string getUsername(const User &user);

    std::string getEmail(const User &user);

    std::string getFirstName(const User &user);

    std::string getLastName(const User &user);

    int addUser(const User &user);

    std::string info(const User &user);

    bool isUsernameExist(const User &user);

    bool isEmailExist(const User &user);
};

#endif // BACKEND_USERCONTROLLER_H

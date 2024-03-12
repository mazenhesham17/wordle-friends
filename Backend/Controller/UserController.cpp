#include "UserController.h"

UserController *UserController::instance = nullptr;

UserController *UserController::getInstance()
{
    if (instance == nullptr)
        instance = new UserController();
    return instance;
}

User UserController::createUser(const jsoncons::json &json)
{
    User user;
    user.setUsername(json["username"].as<std::string>());
    user.setFirstName(json["firstName"].as<std::string>());
    user.setLastName(json["lastName"].as<std::string>());
    user.setEmail(json["email"].as<std::string>());
    user.setPassword(json["password"].as<std::string>());
    return user;
}

User UserController::retrieveUserFromDB(const int &userID)
{
    User user;
    user.setUserID(userID);
    user.setUsername(getUsernameByUserID(userID));
    user.setFirstName(getFirstNameByUserID(userID));
    user.setLastName(getLastNameByUserID(userID));
    user.setEmail(getEmailByUserID(userID));
    return user;
}

std::string UserController::getUsername(const User &user)
{
    return user.getUsername();
}

std::string UserController::getEmail(const User &user)
{
    return user.getEmail();
}

std::string UserController::getFirstName(const User &user)
{
    return user.getFirstName();
}

std::string UserController::getLastName(const User &user)
{
    return user.getLastName();
}

int UserController::addUser(const User &user)
{
    return addPlayer(user.getUsername().c_str(),
                     user.getFirstName().c_str(),
                     user.getLastName().c_str(),
                     user.getEmail().c_str(),
                     user.getPassword().c_str());
}

bool UserController::isUsernameExist(const User &user)
{
    return dbIsUsernameExist(user.getUsername());
}

bool UserController::isEmailExist(const User &user)
{
    return dbIsEmailExist(user.getEmail());
}

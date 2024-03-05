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

User UserController::retriveUserFromDB(const int &userID)
{
    User user;
    user.setUserID(userID);
    user.setUsername(getUsernameByUserID(userID));
    user.setFirstName(getFirstNameByUserID(userID));
    user.setLastName(getLastNameByUserID(userID));
    user.setEmail(getEmailByUserID(userID));
    return user;
}

int UserController::addUser(const User &user)
{
    return addPlayer(user.getUsername().c_str(),
                     user.getFirstName().c_str(),
                     user.getLastName().c_str(),
                     user.getEmail().c_str(),
                     user.getPassword().c_str());
}

std::string UserController::successfulAddition(const int &userID)
{
    return R"({"userID":")" + std::to_string(userID) + R"("})";
}
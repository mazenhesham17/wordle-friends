#include "UserAPI.h"

UserAPI *UserAPI::instance = nullptr;

UserAPI::UserAPI()
{
    responseController = ResponseController::getInstance();
    userController = UserController::getInstance();
}

UserAPI *UserAPI::getInstance()
{
    if (instance == nullptr)
        instance = new UserAPI();
    return instance;
}

Response UserAPI::login(const std::string &identifier, const std::string &password)
{
    int resCode;
    std::regex emailRegex(R"(^[\w._-]+@[\w.]+\.[\w]{2,4}$)");
    if (std::regex_match(identifier, emailRegex))
    {
        resCode = checkPasswordByEmailAddress(identifier, password);
    }
    else
    {
        std::regex usernameRegex(R"(^[\w_]{3,30}$)");
        if (std::regex_match(identifier, usernameRegex))
        {
            resCode = checkPasswordByUsername(identifier, password);
        }
        else
        {
            Response response;
            responseController->setFailure(response, "Invalid email or username");
            return response;
        }
    }
    Response response;
    if (resCode == -1)
    {
        responseController->setFailure(response, "user not found");
    }
    else if (resCode == 0)
    {
        responseController->setFailure(response, "wrong password");
    }
    else
    {
        int userID = resCode;
        int userType = getUserTypeByUserID(userID);
        TokenController *tokenController = TokenController::getInstance();
        responseController->setSuccess(response, tokenController->createToken(userID, userType));
    }
    return response;
}

Response UserAPI::registerUser(const User &user)
{
    Response response;
    if (userController->getFirstName(user).size() < 3)
    {
        responseController->setFailure(response, "first name is too short");
        return response;
    }
    else if (userController->getLastName(user).size() < 3)
    {
        responseController->setFailure(response, "last name is too short");
        return response;
    }
    else if (userController->getUsername(user).size() < 3)
    {
        responseController->setFailure(response, "username is too short");
        return response;
    }
    else if (userController->getUsername(user).size() > 30)
    {
        responseController->setFailure(response, "username is too long");
        return response;
    }
    else
    {
        std::regex emailRegex(R"(^[\w._-]+@[\w.]+\.[\w]{2,4}$)");
        if (!std::regex_match(userController->getEmail(user), emailRegex))
        {
            responseController->setFailure(response, "invalid email");
            return response;
        }
    }

    if (userController->isUsernameExist(user))
    {
        responseController->setFailure(response, "username already exist");
    }
    else if (userController->isEmailExist(user))
    {
        responseController->setFailure(response, "email already exist");
    }
    else
    {
        UserController *userController = UserController::getInstance();
        int userID = userController->addUser(user);
        int userType = getUserTypeByUserID(userID);
        TokenController *tokenController = TokenController::getInstance();
        responseController->setSuccess(response, tokenController->createToken(userID, userType));
    }
    return response;
}

Response UserAPI::info(const int &userType)
{
    Response response;
    std::string userTypeStr = R"({ "userType": ")";
    if (userType == 0)
    {
        userTypeStr += "admin";
    }
    else
    {
        userTypeStr += "player";
    }
    userTypeStr += R"("})";
    responseController->setSuccess(response, userTypeStr);
    return response;
}
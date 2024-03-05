#include "UserAPI.h"

UserAPI *UserAPI::instance = nullptr;

UserAPI *UserAPI::getInstance()
{
    if (instance == nullptr)
        instance = new UserAPI();
    return instance;
}

Response UserAPI::login(const std::string &identifier, const std::string &password)
{
    int resCode;
    if (identifier.find('@') != -1)
    {
        resCode = checkPasswordByEmailAddress(identifier, password);
    }
    else
    {
        resCode = checkPasswordByUsername(identifier, password);
    }
    ResponseController *responseController = ResponseController::getInstance();
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
    ResponseController *responseController = ResponseController::getInstance();
    Response response;
    if (isUsernameExist(user.getUsername()))
    {
        responseController->setFailure(response, "username already exist");
    }
    else if (isEmailExist(user.getEmail()))
    {
        responseController->setFailure(response, "email already exist");
    }
    else
    {
        UserController *userController = UserController::getInstance();
        int userID = userController->addUser(user);
        responseController->setSuccess(response, userController->successfulAddition(userID));
    }
    return response;
}

Response UserAPI::info(const int &userType)
{
    ResponseController *responseController = ResponseController::getInstance();
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
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

Response UserAPI::newSingleGame(const std::string &token, const std::string &word)
{
    ResponseController *responseController = ResponseController::getInstance();
    Response response;
    try
    {
        auto decoded = jwt::decode(token);
        int userID = std::stoi(decoded.get_payload_claim("userID").as_string());
        int userType = decoded.get_payload_claim("userType").as_string() == "admin" ? 0 : 1;
        if (userType == 0)
        {
            responseController->setFailure(response, "admin cannot play game");
        }
        else
        {
            int gameID = addGame(word.c_str());
            addPlayerToGame(userID, gameID);
            responseController->setSuccess(response, GameWebView::getInstance()->newSingleGame(gameID));
        }
    }
    catch (const std::exception &e)
    {
        responseController->setFailure(response, "invalid token");
    }
    return response;
}
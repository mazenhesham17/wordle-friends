#include <jsoncons/json.hpp>
#include <jwt-cpp/jwt.h>
#include "../Database/constants.h"
#include "../Database/dml.h"
#include "../Database/dql.h"
#include "../WebView/TokenWebView.h"
#include "../WebView/AdminWebView.h"
#include "../WebView/PlayerWebView.h"
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
        TokenWebView *tokenWebView = TokenWebView::getInstance();
        auto token = jwt::create()
                         .set_type("JWS")
                         .set_issuer("server")
                         .set_payload_claim("userID", jwt::claim(std::to_string(userID)))
                         .set_payload_claim("userType", jwt::claim(std::string(userType == 0 ? "admin" : "player")))
                         .sign(jwt::algorithm::hs256{SECRET_KEY});
        responseController->setSuccess(response, tokenWebView->token(token));
    }
    return response;
}

Response UserAPI::registerUser(const std::string &username, const std::string &firstName, const std::string &lastName, const std::string &email, const std::string &password)
{
    ResponseController *responseController = ResponseController::getInstance();
    Response response;
    if (isUsernameExist(username))
    {
        responseController->setFailure(response, "username already exist");
    }
    else if (isEmailExist(email))
    {
        responseController->setFailure(response, "email already exist");
    }
    else
    {
        int userID = addPlayer(username.c_str(), firstName.c_str(), lastName.c_str(), email.c_str(), password.c_str());
        TokenWebView *tokenWebView = TokenWebView::getInstance();
        auto token = jwt::create()
                         .set_type("JWS")
                         .set_issuer("server")
                         .set_payload_claim("userID", jwt::claim(std::to_string(userID)))
                         .set_payload_claim("userType", jwt::claim(std::string("player")))
                         .sign(jwt::algorithm::hs256{SECRET_KEY});
        responseController->setSuccess(response, tokenWebView->token(token));
    }
    return response;
}

Response UserAPI::profile(const std::string &token)
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
            std::string username = getUsernameByUserID(userID);
            std::string email = getEmailByUserID(userID);
            responseController->setSuccess(response, AdminWebView::getInstance()->profile(username, email));
        }
        else
        {
            std::string username = getUsernameByUserID(userID);
            std::string firstName = getFirstNameByUserID(userID);
            std::string lastName = getLastNameByUserID(userID);
            std::string email = getEmailByUserID(userID);
            responseController->setSuccess(response, PlayerWebView::getInstance()->profile(username, firstName, lastName, email));
        }
    }
    catch (const std::exception &e)
    {
        responseController->setFailure(response, "invalid token");
    }
    return response;
}
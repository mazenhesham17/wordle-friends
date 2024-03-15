#include "TokenController.h"

using namespace jwt;

TokenController *TokenController::instance = nullptr;

TokenController *TokenController::getInstance()
{
    if (instance == nullptr)
        instance = new TokenController();
    return instance;
}

std::string TokenController::createToken(int userID, int userType)
{
    auto token = jwt::create()
                     .set_type("JWS")
                     .set_issuer("server")
                     .set_payload_claim("userID", jwt::claim(std::to_string(userID)))
                     .set_payload_claim("userType", jwt::claim(std::string(userType == 0 ? "admin" : "player")))
                     .sign(jwt::algorithm::hs256{SECRET_KEY});
    return TokenWebView::getInstance()->token(token, userType == 0 ? "admin" : "player");
}

bool TokenController::verifyToken(const std::string &token)
{
    if (token.empty())
        return false;
    try
    {
        jwt::decoded_jwt decoded = jwt::decode(token);
        auto verifier = jwt::verify()
                            .allow_algorithm(jwt::algorithm::hs256{SECRET_KEY})
                            .with_issuer("server");
        verifier.verify(decoded);
        return true;
    }
    catch (const std::exception &error)
    {
        return false;
    }
}

bool TokenController::isUserAdmin(const std::string &token)
{
    jwt::decoded_jwt decoded = jwt::decode(token);
    return decoded.get_payload_claim("userType").as_string() == "admin";
}

bool TokenController::isUserPlayer(const std::string &token)
{
    jwt::decoded_jwt decoded = jwt::decode(token);
    return decoded.get_payload_claim("userType").as_string() == "player";
}

int TokenController::getUserID(const std::string &token)
{
    jwt::decoded_jwt decoded = jwt::decode(token);
    return std::stoi(decoded.get_payload_claim("userID").as_string());
}

int TokenController::getUserType(const std::string &token)
{
    jwt::decoded_jwt decoded = jwt::decode(token);
    return decoded.get_payload_claim("userType").as_string() == "admin" ? 0 : 1;
}
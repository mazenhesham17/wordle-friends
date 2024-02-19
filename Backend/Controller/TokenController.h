#ifndef BACKEND_TOKENCONTROLLER_H
#define BACKEND_TOKENCONTROLLER_H

#include <jwt-cpp/jwt.h>
#include <string>
#include "../Database/constants.h"
#include "../WebView/TokenWebView.h"

class TokenController
{
    static TokenController *instance;

    TokenController(){};

public:
    static TokenController *getInstance();

    std::string createToken(int userID, int userType);

    bool verifyToken(const std::string &token);

    bool isUserAdmin(const std::string &token);

    bool isUserPlayer(const std::string &token);

    int getUserID(const std::string &token);

    int getUserType(const std::string &token);
};

#endif // BACKEND_TOKENCONTROLLER_H

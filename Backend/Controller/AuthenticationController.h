#ifndef BACKEND_AUTHENTICATIONCONTROLLER_H
#define BACKEND_AUTHENTICATIONCONTROLLER_H

#include <string>
#include "TokenController.h"


class AuthenticationController {
    static AuthenticationController *instance;

    TokenController *tokenController;

    AuthenticationController();

public:

    static AuthenticationController *getInstance();

    bool isAuthenticatedUser(const std::string &token);

    bool isAuthenticatedAdmin(const std::string &token);

    bool isAuthenticatedPlayer(const std::string &token);
};


#endif //BACKEND_AUTHENTICATIONCONTROLLER_H

#ifndef BACKEND_PLAYERCONTROLLER_H
#define BACKEND_PLAYERCONTROLLER_H

#include <string>
#include "BaseController.h"
#include "../Database/dql.h"
#include "../Model/Player.h"
#include "../WebView/PlayerWebView.h"

class PlayerController : public BaseController
{

    static PlayerController *instance;

    PlayerController(){};

public:
    static PlayerController *getInstance();

    std::string profile(const User *user) override;

    Player createPlayer(const User *user);
};

#endif // BACKEND_PLAYERCONTROLLER_H

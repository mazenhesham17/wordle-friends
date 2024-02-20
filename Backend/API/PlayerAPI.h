#ifndef BACKEND_PLAYERAPI_H
#define BACKEND_PLAYERAPI_H

#include "../Controller/GameController.h"
#include "../Controller/PlayerController.h"
#include "../Controller/ResponseController.h"
#include "../Model/Player.h"
#include "../Model/Response.h"

class PlayerAPI
{
    static PlayerAPI *instance;

    PlayerAPI() {}

public:
    static PlayerAPI *getInstance();

    Response profile(const User *player);

    Response newSingleGame(const std::string &word, const int &playerID);
};

#endif // BACKEND_PLAYERAPI_H

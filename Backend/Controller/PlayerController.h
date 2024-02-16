#ifndef BACKEND_PLAYERCONTROLLER_H
#define BACKEND_PLAYERCONTROLLER_H

#include <string>
#include "../Model/Player.h"

class PlayerController
{

    static PlayerController *instance;

    PlayerController(){};

public:
    static PlayerController *getInstance();

    std::string profile(const Player &player);
};

#endif // BACKEND_PLAYERCONTROLLER_H

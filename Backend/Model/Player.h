#ifndef BACKEND_PLAYER_H
#define BACKEND_PLAYER_H

#include "User.h"

class Player : public User
{
public:
    Player() = default;

    Player(const User &user);
};

#endif // BACKEND_PLAYER_H

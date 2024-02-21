#include "Admin.h"

Admin::Admin(const User &user) : User(user) {}

int Admin::getUserCounts() const
{
    return playerCounts;
}

void Admin::setUserCounts(int userCounts)
{
    Admin::playerCounts = userCounts;
}
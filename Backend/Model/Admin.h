#ifndef BACKEND_ADMIN_H
#define BACKEND_ADMIN_H

#include <utility>
#include "User.h"

class Admin : public User
{
    int playerCounts;

public:
    Admin() = default;

    Admin(const User &user);

    int getUserCounts() const;

    void setUserCounts(int userCounts);
};

#endif // BACKEND_ADMIN_H

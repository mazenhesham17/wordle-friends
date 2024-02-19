#ifndef BACKEND_ADMIN_H
#define BACKEND_ADMIN_H

#include "User.h"

class Admin : public User
{
public:
    Admin() = default;

    Admin(const User &user);

};

#endif // BACKEND_ADMIN_H

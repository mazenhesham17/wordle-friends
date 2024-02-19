#ifndef BACKEND_ADMINAPI_H
#define BACKEND_ADMINAPI_H

#include "../Model/User.h"
#include "../Model/Response.h"

class AdminAPI
{
    static AdminAPI *instance;

    AdminAPI() {}

public:
    static AdminAPI *getInstance();

    Response profile(const User *admin);
};

#endif // BACKEND_ADMINAPI_H

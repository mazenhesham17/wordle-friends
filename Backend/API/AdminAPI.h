#ifndef BACKEND_ADMINAPI_H
#define BACKEND_ADMINAPI_H

#include "../Model/Admin.h"
#include "../Model/Response.h"

class AdminAPI
{
    static AdminAPI *instance;

    AdminAPI() {}

public:
    static AdminAPI *getInstance();

    Response profile(const Admin &admin);
};

#endif // BACKEND_ADMINAPI_H

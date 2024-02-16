#ifndef BACKEND_ADMINCONTROLLER_H
#define BACKEND_ADMINCONTROLLER_H

#include <string>
#include "../Model/Admin.h"

class AdminController
{
    static AdminController *instance;

    AdminController(){};

public:
    static AdminController *getInstance();

    std::string profile(const Admin &admin);
};

#endif // BACKEND_ADMINCONTROLLER_H

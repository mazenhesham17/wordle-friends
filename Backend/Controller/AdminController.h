#ifndef BACKEND_ADMINCONTROLLER_H
#define BACKEND_ADMINCONTROLLER_H

#include <string>
#include "../Model/Admin.h"
#include "BaseController.h"

class AdminController : public BaseController
{
    static AdminController *instance;

    AdminController(){};

public:
    static AdminController *getInstance();

    std::string profile(const User *user) override;
};

#endif // BACKEND_ADMINCONTROLLER_H

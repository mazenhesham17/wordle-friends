#ifndef BACKEND_ADMINCONTROLLER_H
#define BACKEND_ADMINCONTROLLER_H

#include <string>
#include "BaseController.h"
#include "../Database/dql.h"
#include "../Model/Admin.h"
#include "../WebView/AdminWebView.h"

class AdminController : public BaseController
{
    static AdminController *instance;

    AdminController(){};

public:
    static AdminController *getInstance();

    std::string profile(const User *user) override;

    std::string dashboard(const Admin &admin);

    Admin createAdmin(const User *user);
};

#endif // BACKEND_ADMINCONTROLLER_H

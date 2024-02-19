#ifndef BACKEND_ADMINCONTROLLER_H
#define BACKEND_ADMINCONTROLLER_H

#include <string>
#include "BaseController.h"
#include "../Model/Admin.h"
#include "../WebView/AdminWebView.h"

class AdminController : public BaseController
{
    static AdminController *instance;

    AdminController(){};

public:
    static AdminController *getInstance();

    std::string profile(const User *user) override;
};

#endif // BACKEND_ADMINCONTROLLER_H

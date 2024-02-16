#include "AdminController.h"
#include "../WebView/AdminWebView.h"
#include <iostream>

AdminController *AdminController::instance = nullptr;

AdminController *AdminController::getInstance()
{
    if (instance == nullptr)
    {
        instance = new AdminController();
    }
    return instance;
}

std::string AdminController::profile(const Admin &admin)
{
    std::cout << "Inside Web View" << std::endl;
    return AdminWebView::getInstance()->profile(admin.getUsername(), admin.getEmail());
}
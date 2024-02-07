#include "AdminWebView.h"
#include <iostream>

AdminWebView *AdminWebView::instance = nullptr;

AdminWebView *AdminWebView::getInstance()
{
    if (instance == nullptr)
        instance = new AdminWebView();
    return instance;
}

std::string AdminWebView::profile(const std::string &username, const std::string &email)
{
    std::string profile = R"({
        "username": ")" + username +
                          R"(","email": ")" + email + R"(", "userType" : "admin" })";
    return profile;
}

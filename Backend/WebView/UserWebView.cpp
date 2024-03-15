#include "UserWebView.h"

UserWebView *UserWebView::instance = nullptr;

UserWebView::UserWebView()
{
}

UserWebView *UserWebView::getInstance()
{
    if (instance == nullptr)
        instance = new UserWebView();
    return instance;
}

std::string UserWebView::userInfo(const std::string &username, const std::string &firstName, const std::string &lastName, const std::string &userType)
{
    std::string userInfo = R"({"username":")" + username + R"(","firstName":")" + firstName + R"(","lastName":")" + lastName + R"(","userType":")" + userType + R"("})";
    return userInfo;
}
#ifndef BACKEND_USERWEBVIEW_H
#define BACKEND_USERWEBVIEW_H

#include <string>

class UserWebView
{
    static UserWebView *instance;

    UserWebView();

public:
    static UserWebView *getInstance();
    std::string userInfo(const std::string &username, const std::string &firstName, const std::string &lastName, const std::string &userType);
};

#endif // BACKEND_USERWEBVIEW_H

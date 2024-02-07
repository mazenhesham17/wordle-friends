#ifndef BACKEND_ADMINWEBVIEW_H
#define BACKEND_ADMINWEBVIEW_H
#include <string>

class AdminWebView
{
    static AdminWebView *instance;
    AdminWebView(){};

public:
    static AdminWebView *getInstance();
    std::string profile(const std::string &username, const std::string &email);
};

#endif // BACKEND_ADMINWEBVIEW_H

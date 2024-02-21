#ifndef BACKEND_PLAYERWEBVIEW_H
#define BACKEND_PLAYERWEBVIEW_H

#include <iostream>
#include <string>

class PlayerWebView
{
    static PlayerWebView *instance;

    PlayerWebView(){};

public:
    static PlayerWebView *getInstance();

    std::string profile(const std::string &username, const std::string &firstName, const std::string &lastName,
                        const std::string &email, const int &wins, const int &games);
};

#endif // BACKEND_PLAYERWEBVIEW_H

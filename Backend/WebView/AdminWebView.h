#ifndef BACKEND_ADMINWEBVIEW_H
#define BACKEND_ADMINWEBVIEW_H

#include <iostream>
#include <string>

class AdminWebView
{
    static AdminWebView *instance;

    AdminWebView(){};

public:
    static AdminWebView *getInstance();

    std::string profile(const std::string &username, const std::string &email);

    std::string dashboard( const int &totalPlayers, const int &totalGames, const int &totalWins);
};

#endif // BACKEND_ADMINWEBVIEW_H

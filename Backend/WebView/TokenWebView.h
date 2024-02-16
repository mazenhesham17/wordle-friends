#ifndef BACKEND_TOKENWEBVIEW_H
#define BACKEND_TOKENWEBVIEW_H

#include <string>

class TokenWebView
{
    static TokenWebView *instance;

    TokenWebView(){};

public:
    static TokenWebView *getInstance();

    std::string token(const std::string &token);
};

#endif // BACKEND_TOKENWEBVIEW_H

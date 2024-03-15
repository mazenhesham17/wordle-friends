#include "TokenWebView.h"

TokenWebView *TokenWebView::instance = nullptr;

TokenWebView *TokenWebView::getInstance()
{
    if (instance == nullptr)
        instance = new TokenWebView();
    return instance;
}

std::string TokenWebView::token(const std::string &token, const std::string &userType)
{
    return R"( {"token": ")" + token + R"(", "userType" : ")" + userType + R"("})";
}

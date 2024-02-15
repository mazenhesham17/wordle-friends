#include "GameWebView.h"

GameWebView *GameWebView::instance = nullptr;

GameWebView *GameWebView::getInstance()
{
    if (instance == nullptr)
        instance = new GameWebView();
    return instance;
}

std::string GameWebView::newSingleGame(const int &gameID)
{
    return R"( {"gameID": )" + std::to_string(gameID) + R"( } )";
}
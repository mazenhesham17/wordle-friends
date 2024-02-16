#ifndef BACKEND_GAMEWEBVIEW_H
#define BACKEND_GAMEWEBVIEW_H

#include <string>

class GameWebView
{
    static GameWebView *instance;

    GameWebView(){};

public:
    static GameWebView *getInstance();

    std::string newSingleGame(const int &gameID);
};

#endif // BACKEND_GAMEWEBVIEW_H

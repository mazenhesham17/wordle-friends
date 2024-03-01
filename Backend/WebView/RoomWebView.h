#ifndef BACKEND_ROOMWEBVIEW_H
#define BACKEND_ROOMWEBVIEW_H

#include <string>

class RoomWebView
{
    static RoomWebView *instance;
    RoomWebView(){};

public:
    static RoomWebView *getInstance();
    std::string newRoom(const std::string &roomID);
};

#endif // BACKEND_ROOMWEBVIEW_H

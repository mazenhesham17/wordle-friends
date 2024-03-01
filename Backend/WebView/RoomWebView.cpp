#include "RoomWebView.h"

RoomWebView *RoomWebView::instance = nullptr;

RoomWebView *RoomWebView::getInstance()
{
    if (instance == nullptr)
    {
        instance = new RoomWebView();
    }
    return instance;
}

std::string RoomWebView::newRoom(const std::string &roomID)
{
    return R"( {"roomID": ")" + roomID + R"(" } )";
}
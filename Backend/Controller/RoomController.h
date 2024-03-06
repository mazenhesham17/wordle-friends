#ifndef BACKEND_ROOMCONTROLLER_H
#define BACKEND_ROOMCONTROLLER_H

#include <string>
#include <vector>
#include <boost/asio/ip/tcp.hpp>
#include "../Database/dql.h"
#include "../Model/Room.h"
#include "../Model/RoomContainer.h"
#include "../WebView/RoomWebView.h"

class Session;

class RoomController
{
    static RoomController *instance;

    RoomController(){};

    RoomContainer roomContainer;

    Room &getRoom(const std::string &roomID);

public:
    static RoomController *getInstance();

    std::string createGameRoom(const int &playerID, const int &gameID, const std::string &type);

    std::string createChatRoom(int playerID, int friendID);

    bool isRoomExist(const std::string &roomID);

    bool isRoomFull(const std::string &roomID);

    void addSession(const std::string &roomID, std::shared_ptr<Session> &session, const int &playerID);

    void broadcast(const std::string &message, const std::string &roomID, const int &playerID);

    void blockRoom(const std::string &roomID);

    int getConnectedPlayersCount(const std::string &roomID);

    int getFinishedPlayersCount(const std::string &roomID);

    void endAllSessions(const std::string &roomID);
};

#endif // BACKEND_ROOMCONTROLLER_H

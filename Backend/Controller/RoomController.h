#ifndef BACKEND_ROOMCONTROLLER_H
#define BACKEND_ROOMCONTROLLER_H

#include <string>
#include <vector>
#include "../Database/dql.h"
#include "../Model/Room.h"
#include "../Model/RoomContainer.h"
#include "../WebView/RoomWebView.h"
#include "../Controller/ChatController.h"

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

    std::string chatRoomName(int playerID, int friendID);

    std::string roomView(const std::string &roomID);

    std::string createChatRoom(const int &playerID, const int &friendID);

    bool isRoomExist(const std::string &roomID);

    bool isRoomFull(const std::string &roomID);

    void addSession(const std::string &roomID, std::shared_ptr<Session> &session, const int &playerID);

    void broadcast(const std::string &message, const std::string &roomID, const int &playerID, const bool &sync = false);

    void chatBroadcast(const std::string &message, const std::string &roomID);

    void blockRoom(const std::string &roomID);

    void closeRoom(const std::string &roomID);

    int getConnectedSessionsCount(const std::string &roomID);

    int getFinishedSessionsCount(const std::string &roomID);

    void endAllSessions(const std::string &roomID);
};

#endif // BACKEND_ROOMCONTROLLER_H

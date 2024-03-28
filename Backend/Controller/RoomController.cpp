#include "RoomController.h"
#include "../Session/Session.h"

RoomController *RoomController::instance = nullptr;

RoomController *RoomController::getInstance()
{
    if (instance == nullptr)
    {
        instance = new RoomController();
    }
    return instance;
}

std::string RoomController::createGameRoom(const int &playerID, const int &gameID, const std::string &type)
{
    int game_count = getTotalGamesCount();
    std::string roomID =
        std::to_string(playerID) + type + std::to_string(game_count + 1) + "G" + std::to_string(gameID);
    Room room(roomID, (type == "S" ? 1 : 2));
    roomContainer.addRoom(room);
    return RoomWebView::getInstance()->room(roomID);
}

std::string RoomController::chatRoomName(int playerID, int friendID)
{
    if (playerID > friendID)
    {
        std::swap(playerID, friendID);
    }
    int chatID = ChatController::getInstance()->getChatID(playerID, friendID);
    return std::to_string(playerID) + "F" + std::to_string(friendID) + "C" + std::to_string(chatID);
}

std::string RoomController::roomView(const std::string &roomID)
{
    return RoomWebView::getInstance()->room(roomID);
}

std::string RoomController::createChatRoom(const int &playerID, const int &friendID)
{
    std::string roomID = chatRoomName(playerID, friendID);
    Room room(roomID, 2);
    roomContainer.addRoom(room);
    return roomView(roomID);
}

bool RoomController::isRoomExist(const std::string &roomID)
{
    return roomContainer.isRoomExist(roomID) && !getRoom(roomID).isClosed();
}

bool RoomController::isRoomFull(const std::string &roomID)
{
    Room &room = getRoom(roomID);
    return room.getSessions().size() == room.getMaxConnections();
}

Room &RoomController::getRoom(const std::string &roomID)
{
    return roomContainer.getRoom(roomID);
}

void RoomController::addSession(const std::string &roomID, std::shared_ptr<Session> &session, const int &playerID)
{
    getRoom(roomID).addSession(session, playerID);
}

void RoomController::broadcast(const std::string &message, const std::string &roomID, const int &playerID, const bool &sync)
{
    Room &room = getRoom(roomID);
    for (auto &session : room.getSessions())
    {
        if (session->getPlayerID() != playerID)
        {
            if (sync)
            {
                session->send(message);
            }
            else
            {
                session->asyncSend(message);
            }
        }
    }
}

void RoomController::chatBroadcast(const std::string &message, const std::string &roomID)
{
    Room &room = getRoom(roomID);
    for (auto &session : room.getSessions())
    {
        if (session->isConnected())
        {
            session->asyncSend(message);
        }
    }
}

int RoomController::getConnectedSessionsCount(const std::string &roomID)
{
    Room &room = getRoom(roomID);
    int cnt = 0;
    for (auto &session : room.getSessions())
    {
        if (session->isConnected())
        {
            cnt++;
        }
    }
    room.getRoomCV().notify_all();
    return cnt;
}

int RoomController::getFinishedSessionsCount(const std::string &roomID)
{
    int cnt = 0;
    for (auto &session : getRoom(roomID).getSessions())
    {
        if (session->isFinished())
        {
            cnt++;
        }
    }
    return cnt;
}

void RoomController::blockRoom(const std::string &roomID)
{
    Room &room = getRoom(roomID);
    std::unique_lock<std::mutex> lock(room.getRoomMutex());
    auto now = std::chrono::system_clock::now();
    room.getRoomCV().wait_until(lock, now + std::chrono::seconds(60), [&]()
                                { return getConnectedSessionsCount(roomID) == room.getMaxConnections(); });
}

void RoomController::closeRoom(const std::string &roomID)
{
    getRoom(roomID).closeRoom();
}

void RoomController::endAllSessions(const std::string &roomID)
{
    Room &room = getRoom(roomID);
    for (auto &session : room.getSessions())
    {
        if (session->isConnected())
        {
            session->close();
        }
    }
}

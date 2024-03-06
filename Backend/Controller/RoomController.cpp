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
    Room room(roomID);
    roomContainer.addRoom(room);
    return RoomWebView::getInstance()->newRoom(roomID);
}

std::string RoomController::createChatRoom(int playerID, int friendID)
{
    if (playerID > friendID)
    {
        std::swap(playerID, friendID);
    }
    std::string roomID = std::to_string(playerID) + "C" + std::to_string(friendID);
    Room room(roomID);
    roomContainer.addRoom(room);
    return RoomWebView::getInstance()->newRoom(roomID);
}

bool RoomController::isRoomExist(const std::string &roomID)
{
    return roomContainer.isRoomExist(roomID);
}

bool RoomController::isRoomFull(const std::string &roomID)
{
    return getRoom(roomID).getSessions().size() == 2;
}

Room &RoomController::getRoom(const std::string &roomID)
{
    return roomContainer.getRoom(roomID);
}

void RoomController::addSession(const std::string &roomID, std::shared_ptr<Session> &session, const int &playerID)
{
    getRoom(roomID).addSession(session, playerID);
}

void RoomController::broadcast(const std::string &message, const std::string &roomID, const int &playerID)
{
    Room &room = getRoom(roomID);
    for (auto &session : room.getSessions())
    {
        if (session->getPlayerID() != playerID)
        {
            session->asyncSend(message);
        }
    }
}

int RoomController::getConnectedPlayersCount(const std::string &roomID)
{
    return getRoom(roomID).getConnectedSessionsCount();
}

int RoomController::getFinishedPlayersCount(const std::string &roomID)
{
    return getRoom(roomID).getFinishedSessionsCount();
}

void RoomController::blockRoom(const std::string &roomID)
{
    getRoom(roomID).blockRoom();
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

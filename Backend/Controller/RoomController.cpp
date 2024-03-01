#include "RoomController.h"

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
    std::string roomID = std::to_string(playerID) + type + std::to_string(game_count + 1) + "G" + std::to_string(gameID);
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

void RoomController::addSocketToRoom(Room &room, int &playerID, tcp::socket &socket)
{
    room.addSocket(playerID, socket);
}

bool RoomController::isRoomExist(const std::string &roomID)
{
    return roomContainer.isRoomExist(roomID);
}

Room &RoomController::getRoom(const std::string &roomID)
{
    return roomContainer.getRoom(roomID);
}

std::vector<int> &RoomController::getPlayerIDs(Room &room)
{
    return room.getPlayerIDs();
}

std::vector<tcp::socket> &RoomController::getSockets(Room &room)
{
    return room.getSockets();
}
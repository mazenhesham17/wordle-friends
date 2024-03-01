#include "Room.h"

Room::Room(std::string roomID)
{
    this->roomID = roomID;
}

Room::Room(Room &&other) noexcept : roomID(std::move(other.roomID)), playerIDs(std::move(other.playerIDs)), sockets(std::move(other.sockets))
{
}

std::string Room::getRoomID() const
{
    return roomID;
}

void Room::setRoomID(const std::string &roomID)
{
    this->roomID = roomID;
}

std::vector<int> &Room::getPlayerIDs()
{
    return playerIDs;
}

std::vector<tcp::socket> &Room::getSockets()
{
    return sockets;
}

void Room::addSocket(const int playerID, tcp::socket &socket)
{
    playerIDs.push_back(playerID);
    sockets.push_back(std::move(socket));
}

Room::~Room()
{
    for (auto &socket : sockets)
    {
        socket.close();
    }
}
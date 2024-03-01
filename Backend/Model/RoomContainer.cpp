#include "RoomContainer.h"

void RoomContainer::addRoom(Room &room)
{
    roomIDToidx[room.getRoomID()] = rooms.size();
    rooms.emplace_back(std::move(room));
}

bool RoomContainer::isRoomExist(const std::string &roomID)
{
    return roomIDToidx.find(roomID) != roomIDToidx.end();
}

Room &RoomContainer::getRoom(const std::string &roomID)
{
    return rooms[roomIDToidx[roomID]];
}
#include "RoomContainer.h"
#include "Room.h"

void RoomContainer::addRoom(Room &room)
{
    roomIDToRoomIndex[room.getRoomID()] = (int)rooms.size();
    rooms.emplace_back(std::move(room));
}

bool RoomContainer::isRoomExist(const std::string &roomID)
{
    return roomIDToRoomIndex.find(roomID) != roomIDToRoomIndex.end();
}

Room &RoomContainer::getRoom(const std::string &roomID)
{
    return rooms[roomIDToRoomIndex[roomID]];
}
#ifndef BACKEND_ROOMCONTAINER_H
#define BACKEND_ROOMCONTAINER_H

#include <string>
#include <vector>
#include <map>
#include "Room.h"

class RoomContainer
{
    std::vector<Room> rooms;

    std::map<std::string, int> roomIDToidx;

public:
    RoomContainer() = default;

    void addRoom(Room &room);

    bool isRoomExist(const std::string &roomID);

    Room &getRoom(const std::string &roomID);
};

#endif // BACKEND_ROOMCONTAINER_H

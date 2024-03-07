#include "Room.h"
#include "../Session/Session.h"

Room::Room(std::string roomID, int max_connections) : roomID(std::move(roomID)), max_connections(max_connections)
{
}

Room::Room(Room &&other) noexcept : roomID(std::move(other.roomID)), max_connections(other.max_connections), sessions(std::move(other.sessions))
{
}

std::string Room::getRoomID() const
{
    return roomID;
}

void Room::addSession(std::shared_ptr<Session> &session, const int &playerID)
{
    playerIDToSessionIndex[playerID] = (int)sessions.size();
    sessions.push_back(session);
}

std::vector<std::shared_ptr<Session>> &Room::getSessions()
{
    return sessions;
}

std::condition_variable &Room::getRoomCV()
{
    return roomCV;
}

int Room::getMaxConnections() const
{
    return max_connections;
}

std::mutex &Room::getRoomMutex()
{
    return roomMutex;
}

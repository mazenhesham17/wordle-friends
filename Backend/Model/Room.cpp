#include "Room.h"
#include "../Session/Session.h"

Room::Room(std::string roomID)
{
    this->roomID = std::move(roomID);
}

Room::Room(Room &&other) noexcept : roomID(std::move(other.roomID)), sessions(std::move(other.sessions))
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

void Room::blockRoom()
{
    std::unique_lock<std::mutex> lock(roomMutex);
    auto now = std::chrono::system_clock::now();
    roomCV.wait_until(lock, now + std::chrono::seconds(60), [&]()
                      { return getConnectedSessionsCount() == 2; });
}

int Room::getConnectedSessionsCount()
{
    int cnt = 0;
    for (auto &session : sessions)
    {
        if (session->isConnected())
        {
            cnt++;
        }
    }
    roomCV.notify_all();
    return cnt;
}

int Room::getFinishedSessionsCount()
{
    int cnt = 0;
    for (auto &session : sessions)
    {
        if (session->isFinished())
        {
            cnt++;
        }
    }
    return cnt;
}

std::vector<std::shared_ptr<Session>> &Room::getSessions()
{
    return sessions;
}
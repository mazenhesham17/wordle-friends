#ifndef BACKEND_ROOM_H
#define BACKEND_ROOM_H

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <condition_variable>
#include <memory>

class Session;

class Room
{
    std::string roomID;

    std::vector<std::shared_ptr<Session>> sessions;

    std::map<int, int> playerIDToSessionIndex;

    std::mutex roomMutex;

    std::condition_variable roomCV;

public:
    Room(std::string roomID);

    Room(Room &&other) noexcept;

    std::string getRoomID() const;

    void addSession(std::shared_ptr<Session> &session, const int &playerID);

    std::vector<std::shared_ptr<Session>> &getSessions();

    void blockRoom();

    int getConnectedSessionsCount();

    int getFinishedSessionsCount();
};

#endif // BACKEND_ROOM_H

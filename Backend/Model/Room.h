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
    int max_connections;

    std::string roomID;

    std::vector<std::shared_ptr<Session>> sessions;

    std::map<int, int> playerIDToSessionIndex;

    std::mutex roomMutex;

    std::condition_variable roomCV;

public:
    Room(std::string roomID, int max_connections);

    Room(Room &&other) noexcept;

    void addSession(std::shared_ptr<Session> &session, const int &playerID);

    int getMaxConnections() const;

    std::string getRoomID() const;

    std::vector<std::shared_ptr<Session>> &getSessions();

    std::condition_variable &getRoomCV();

    std::mutex &getRoomMutex();
};

#endif // BACKEND_ROOM_H

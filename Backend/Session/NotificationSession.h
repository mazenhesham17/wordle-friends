#ifndef BACKEND_NOTIFICATIONSESSION_H
#define BACKEND_NOTIFICATIONSESSION_H

#include "Session.h"

class NotificationSession : public Session
{
    std::string notifyRoom;

public:
    NotificationSession(tcp::socket &&socket, const std::string &roomId, int playerId);

    bool isFinished() override;

    void launchSession() override;
};

#endif // BACKEND_NOTIFICATIONSESSION_H

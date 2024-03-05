#ifndef BACKEND_SERVERCONTROLLER_H
#define BACKEND_SERVERCONTROLLER_H

#include <iostream>
#include <memory>
#include <httplib.h>
#include <jsoncons/json.hpp>
#include "SocketController.h"
#include "ResponseController.h"
#include "TokenController.h"
#include "UserController.h"
#include "RoomController.h"
#include "../API/AdminAPI.h"
#include "../API/PlayerAPI.h"
#include "../API/UserAPI.h"
#include "../Model/Admin.h"
#include "../Model/User.h"
#include "../Model/Player.h"
#include "../Session/Session.h"
#include "../Session/SingleGameSession.h"
#include "../Session/DuoGameSession.h"

class ServerController
{
    UserAPI *userApi;
    AdminAPI *adminApi;
    PlayerAPI *playerApi;
    ResponseController *responseController;
    RoomController *roomController;
    TokenController *tokenController;
    UserController *userController;
    SocketController *socketController;
    static ServerController *instance;

    ServerController();

    void requests(httplib::Server &server);

    void connectSocketAndLaunchGameSession(const std::string &roomID, int playerID);

public:
    static ServerController *getInstance();

    void start();
};

#endif // BACKEND_SERVERCONTROLLER_H

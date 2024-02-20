#ifndef BACKEND_SERVERCONTROLLER_H
#define BACKEND_SERVERCONTROLLER_H

#include <iostream>
#include <httplib.h>
#include <jsoncons/json.hpp>
#include "SocketController.h"
#include "TokenController.h"
#include "UserController.h"
#include "../API/AdminAPI.h"
#include "../API/PlayerAPI.h"
#include "../API/UserAPI.h"
#include "../Model/Admin.h"
#include "../Model/User.h"
#include "../Model/Player.h"

class ServerController
{
    UserAPI *userApi;
    AdminAPI *adminApi;
    PlayerAPI *playerApi;
    TokenController *tokenController;
    UserController *userController;
    SocketController *socketController;
    static ServerController *instance;
    ServerController();
    void requests( httplib::Server &server);

public:
    static ServerController *getInstance();
    void start();
};

#endif // BACKEND_SERVERCONTROLLER_H

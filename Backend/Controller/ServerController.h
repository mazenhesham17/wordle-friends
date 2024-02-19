#ifndef BACKEND_SERVERCONTROLLER_H
#define BACKEND_SERVERCONTROLLER_H
#include <iostream>
#include <httplib.h>
#include <jsoncons/json.hpp>
#include "../API/UserAPI.h"
#include "../API/AdminAPI.h"
#include "../API/PlayerAPI.h"
#include "../Controller/TokenController.h"
#include "../Controller/UserController.h"
#include "../Model/User.h"
#include "../Model/Admin.h"
#include "../Model/Player.h"

class ServerController
{
    httplib::Server server;
    UserAPI *userApi;
    AdminAPI *adminApi;
    PlayerAPI *playerApi;
    TokenController *tokenController;
    UserController *userController;
    static ServerController *instance;
    ServerController();

public:
    static ServerController *getInstance();
    void requests();
    void start( int port );
};

#endif // BACKEND_SERVERCONTROLLER_H

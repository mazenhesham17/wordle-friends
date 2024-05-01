#ifndef BACKEND_SERVERCONTROLLER_H
#define BACKEND_SERVERCONTROLLER_H

#include <iostream>
#include <memory>
#include <httplib.h>
#include <jsoncons/json.hpp>
#include "AuthenticationController.h"
#include "ChatController.h"
#include "SocketController.h"
#include "ResponseController.h"
#include "TokenController.h"
#include "UserController.h"
#include "RoomController.h"
#include "GameController.h"
#include "PlayerController.h"
#include "../API/AdminAPI.h"
#include "../API/PlayerAPI.h"
#include "../API/UserAPI.h"
#include "../Model/Admin.h"
#include "../Model/User.h"
#include "../Model/Player.h"
#include "../Session/Session.h"
#include "../Session/SingleGameSession.h"
#include "../Session/DuoGameSession.h"
#include "../Session/ChatSession.h"
#include "../Session/NotificationSession.h"

class ServerController
{
    AuthenticationController *authenticationController;
    UserAPI *userAPI;
    AdminAPI *adminAPI;
    PlayerAPI *playerAPI;
    GameController *gameController;
    ChatController *chatController;
    ResponseController *responseController;
    PlayerController *playerController;
    RoomController *roomController;
    TokenController *tokenController;
    UserController *userController;
    SocketController *socketController;
    static ServerController *instance;

    ServerController();

    void PostRegister(const httplib::Request &req, httplib::Response &res);

    void PostLogin(const httplib::Request &req, httplib::Response &res);

    void GetInfo(const httplib::Request &req, httplib::Response &res);

    void GetDashboard(const httplib::Request &req, httplib::Response &res);

    void GetCheckRoom(const httplib::Request &req, httplib::Response &res);

    void PostNewGame(const httplib::Request &req, httplib::Response &res);

    void PostStartGame(const httplib::Request &req, httplib::Response &res);

    void GetProfile(const httplib::Request &req, httplib::Response &res);

    void GetGames(const httplib::Request &req, httplib::Response &res);

    void PutProfile(const httplib::Request &req, httplib::Response &res);

    void GetFriendsProfile(const httplib::Request &req, httplib::Response &res);

    void GetSearch(const httplib::Request &req, httplib::Response &res);

    void PostAddFriend(const httplib::Request &req, httplib::Response &res);

    void PostNotification(const httplib::Request &req, httplib::Response &res);

    void GetFriendsChat(const httplib::Request &req, httplib::Response &res);

    void GetChat(const httplib::Request &req, httplib::Response &res);

    void GetChatRoom(const httplib::Request &req, httplib::Response &res);

    void PostStartChat(const httplib::Request &req, httplib::Response &res);

    void requests(httplib::Server &server);

    void connectSocketAndLaunchSession(const std::string &roomID, int playerID);

public:
    static ServerController *getInstance();

    void start(int port);
};

#endif // BACKEND_SERVERCONTROLLER_H

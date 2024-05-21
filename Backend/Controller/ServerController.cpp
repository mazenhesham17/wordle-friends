#include "ServerController.h"

ServerController *ServerController::instance = nullptr;

ServerController::ServerController()
{
    userAPI = UserAPI::getInstance();
    adminAPI = AdminAPI::getInstance();
    playerAPI = PlayerAPI::getInstance();
    authenticationController = AuthenticationController::getInstance();
    chatController = ChatController::getInstance();
    tokenController = TokenController::getInstance();
    userController = UserController::getInstance();
    socketController = SocketController::getInstance();
    responseController = ResponseController::getInstance();
    roomController = RoomController::getInstance();
    gameController = GameController::getInstance();
    playerController = PlayerController::getInstance();
}

ServerController *ServerController::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ServerController();
    }
    return instance;
}

void ServerController::connectSocketAndLaunchSession(const std::string &roomID, int playerID)
{
    tcp::socket socket{socketController->getIOContext()};
    socketController->connectSocket(socket);
    std::shared_ptr<Session> session;
    if (roomID.find('S') != -1)
    {
        // single player game
        session = std::make_shared<SingleGameSession>(std::move(socket), roomID, playerID);
    }
    else if (roomID.find('D') != -1)
    {
        // two player game
        session = std::make_shared<DuoGameSession>(std::move(socket), roomID, playerID);
    }
    else if (roomID.find('C') != -1)
    {
        // chat room
        session = std::make_shared<ChatSession>(std::move(socket), roomID, playerID);
    }
    else if (roomID.find('N') != -1)
    {
        // notification room
        session = std::make_shared<NotificationSession>(std::move(socket), roomID, playerID);
    }
    else
    {
        // room not found
        return;
    }
    roomController->addSession(roomID, session, playerID);
    session->launchSession();
}

void ServerController::PostRegister(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Register request of type POST received on thread : " << std::this_thread::get_id() << std::endl;
    nlohmann::json body = nlohmann::json::parse(req.body);
    // jsoncons::json body = jsoncons::json::parse(req.body);
    User user = userController->createUser(body);
    Response response = userAPI->registerUser(user);
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::PostLogin(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Login request of type POST received on thread : " << std::this_thread::get_id() << std::endl;

    // jsoncons::json body = jsoncons::json::parse(req.body);
    nlohmann::json body = nlohmann::json::parse(req.body);
    std::string identifier = body["identifier"];
    std::string password = body["password"];
    Response response = userAPI->login(identifier, password);
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::GetInfo(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Info request of type GET received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    Response response;
    if (!authenticationController->isAuthenticatedUser(token))
    {
        responseController->setFailure(response, "Unauthorized");
        res.set_content(responseController->getJson(response), "application/json");
        res.status = 401;
        return;
    }
    int userID = tokenController->getUserID(token);
    User user = userController->retrieveUserFromDB(userID);

    response = userAPI->info(user);
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::GetDashboard(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Dashboard request of type GET received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    if (!authenticationController->isAuthenticatedAdmin(token))
    {
        res.status = 401;
        return;
    }

    int userID = tokenController->getUserID(token);
    User *user = new Admin(userController->retrieveUserFromDB(userID));
    Admin admin = AdminController::getInstance()->createAdmin(user);
    int offset = std::stoi(req.path_params.at("offset"));
    Response response = adminAPI->dashboard(admin, offset);
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::GetCheckRoom(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Check room request of type GET received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    if (!authenticationController->isAuthenticatedPlayer(token))
    {
        res.status = 401;
        return;
    }

    std::string roomID = req.path_params.at("roomID");
    if (!roomController->isRoomExist(roomID))
    {
        Response response;
        responseController->setFailure(response, "there is no room with this ID");
        res.set_content(responseController->getJson(response), "application/json");
        return;
    }
    if (roomController->isRoomFull(roomID))
    {
        Response response;
        responseController->setFailure(response, "there is no place in the room");
        res.set_content(responseController->getJson(response), "application/json");
        return;
    }
    res.set_content(responseController->success(), "application/json");
}

void ServerController::PostNewGame(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "New game request of type POST received on thread : " << std::this_thread::get_id() << std::endl;

    std::string token = req.get_header_value("Authorization");
    if (!authenticationController->isAuthenticatedPlayer(token))
    {
        res.status = 401;
        return;
    }

    int playerID = tokenController->getUserID(token);
    if (gameController->isPlayerInGame(playerID))
    {
        Response response;
        responseController->setFailure(response, "you are already in a game");
        res.set_content(responseController->getJson(response), "application/json");
        return;
    }

    auto gameType = req.path_params.at("type");
    
    try
    {
        std::string wordle_url = std::getenv("WORDLE_URL");
        httplib::Client client(wordle_url, 5000);
        auto clientResponse = client.Get("/wordle");
        std::string word = nlohmann::json::parse(clientResponse->body)["word"];
        Response response = playerAPI->newGame(word, playerID, gameType);
        res.set_content(responseController->getJson(response), "application/json");
    }
    catch (std::exception &e)
    {
        Response response;
        responseController->setFailure(response, "wordle service is down");
        res.set_content(responseController->getJson(response), "application/json");
    }
}

void ServerController::PostStartGame(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Start game request of type POST received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    if (!authenticationController->isAuthenticatedPlayer(token))
    {
        res.status = 401;
        return;
    }

    int playerID = tokenController->getUserID(token);
    if (gameController->isPlayerInGame(playerID))
    {
        Response response;
        responseController->setFailure(response, "you are already in a game");
        res.set_content(responseController->getJson(response), "application/json");
        return;
    }

    std::string roomID = req.path_params.at("roomID");
    if (!roomController->isRoomExist(roomID))
    {
        Response response;
        responseController->setFailure(response, "there is no room with this ID");
        res.set_content(responseController->getJson(response), "application/json");
        return;
    }
    std::thread(&ServerController::connectSocketAndLaunchSession, this, roomID, playerID).detach();
    res.set_content(responseController->success(), "application/json");
}

void ServerController::GetProfile(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Profile request of type GET received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    Response response;
    if (!authenticationController->isAuthenticatedUser(token))
    {
        responseController->setFailure(response, "Unauthorized");
        res.set_content(responseController->getJson(response), "application/json");
        res.status = 401;
        return;
    }
    int userID = tokenController->getUserID(token);
    int userType = tokenController->getUserType(token);
    User *user;
    if (userType == 0)
    {
        user = new Admin(userController->retrieveUserFromDB(userID));
        response = adminAPI->profile(user);
    }
    else
    {
        user = new Player(userController->retrieveUserFromDB(userID));
        response = playerAPI->profile(user);
    }
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::GetGames(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Game details request of type GET received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    Response response;
    if (!authenticationController->isAuthenticatedPlayer(token))
    {
        responseController->setFailure(response, "Unauthorized");
        res.set_content(responseController->getJson(response), "application/json");
        res.status = 401;
        return;
    }

    int userID = tokenController->getUserID(token);
    int offset = std::stoi(req.path_params.at("offset"));
    response = playerAPI->games(userID, offset);
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::PutProfile(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Profile request of type PUT received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    Response response;
    if (!authenticationController->isAuthenticatedUser(token))
    {
        responseController->setFailure(response, "Unauthorized");
        res.set_content(responseController->getJson(response), "application/json");
        res.status = 401;
        return;
    }

    int userID = tokenController->getUserID(token);
    nlohmann::json body = nlohmann::json::parse(req.body);

    for (auto &element : body.items())
    {
        std::string key = element.key();
        std::string value = element.value();
        response = playerAPI->updatePlayer(userID, key, value);
        // there is a field that is not updated
        if (!responseController->isSuccess(response))
        {
            res.set_content(responseController->getJson(response), "application/json");
            return;
        }
    }
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::GetFriendsProfile(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Friends profile request of type GET received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    Response response;
    if (!authenticationController->isAuthenticatedPlayer(token))
    {
        responseController->setFailure(response, "Unauthorized");
        res.set_content(responseController->getJson(response), "application/json");
        res.status = 401;
        return;
    }

    int userID = tokenController->getUserID(token);
    response = playerAPI->profileFriends(userID);
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::GetSearch(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Search request of type GET received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    Response response;
    if (!authenticationController->isAuthenticatedPlayer(token))
    {
        responseController->setFailure(response, "Unauthorized");
        res.set_content(responseController->getJson(response), "application/json");
        res.status = 401;
        return;
    }

    int userID = tokenController->getUserID(token);
    std::string query = req.path_params.at("query");
    response = playerAPI->search(userID, query);
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::PostAddFriend(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Add friend request of type POST received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    Response response;
    if (!authenticationController->isAuthenticatedPlayer(token))
    {
        responseController->setFailure(response, "Unauthorized");
        res.set_content(responseController->getJson(response), "application/json");
        res.status = 401;
        return;
    }

    int userID = tokenController->getUserID(token);
    int friendID = std::stoi(req.path_params.at("friendID"));
    if (!playerController->isUserIDExist(friendID))
    {
        responseController->setFailure(response, "there is no user with this ID");
        res.set_content(responseController->getJson(response), "application/json");
        return;
    }
    if (userID == friendID)
    {
        responseController->setFailure(response, "you can't add yourself as a friend");
        res.set_content(responseController->getJson(response), "application/json");
        return;
    }
    if (playerController->isFriend(userID, friendID))
    {
        responseController->setFailure(response, "you are already friend with this user");
        res.set_content(responseController->getJson(response), "application/json");
        return;
    }

    response = playerAPI->addFriend(userID, friendID);
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::PostNotification(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Notification request of type POST received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    Response response;
    if (!authenticationController->isAuthenticatedPlayer(token))
    {
        responseController->setFailure(response, "Unauthorized");
        res.set_content(responseController->getJson(response), "application/json");
        res.status = 401;
        return;
    }

    int userID = tokenController->getUserID(token);

    std::string roomID = std::to_string(userID) + "N";

    if (!roomController->isRoomExist(roomID))
    {
        roomController->createNotificationRoom(userID);
    }

    std::thread(&ServerController::connectSocketAndLaunchSession, this, roomID, userID).detach();
    res.set_content(responseController->success(), "application/json");
}

void ServerController::GetFriendsChat(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Friends chat request of type GET received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    if (!authenticationController->isAuthenticatedPlayer(token))
    {
        res.status = 401;
        return;
    }

    int playerID = tokenController->getUserID(token);
    Response response = playerAPI->chatFriends(playerID);
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::GetChat(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Chat request of type GET received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    if (!authenticationController->isAuthenticatedPlayer(token))
    {
        res.status = 401;
        return;
    }

    int chatID = std::stoi(req.path_params.at("chatID"));

    Response response;
    if (!chatController->isChatExist(chatID))
    {
        responseController->setFailure(response, "there is no chat with this ID");
        res.set_content(responseController->getJson(response), "application/json");
        return;
    }

    int playerID = tokenController->getUserID(token);

    if (!chatController->isPlayerInChat(chatID, playerID))
    {
        responseController->setFailure(response, "you are not in this chat");
        res.set_content(responseController->getJson(response), "application/json");
        res.status = 401;
        return;
    }
    responseController->setSuccess(response, chatController->getChat(chatID, playerID));
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::GetChatRoom(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Chat ID request of type GET received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    if (!authenticationController->isAuthenticatedPlayer(token))
    {
        res.status = 401;
        return;
    }

    int playerID = tokenController->getUserID(token);
    int friendID = std::stoi(req.path_params.at("friendID"));
    std::string roomID = roomController->chatRoomName(playerID, friendID);
    Response response;
    if (roomController->isRoomExist(roomID))
    {
        responseController->setSuccess(response, roomController->roomView(roomID));
    }
    else
    {
        responseController->setSuccess(response, roomController->createChatRoom(playerID, friendID));
    }
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::PostStartChat(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Start chat request of type POST received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    if (!authenticationController->isAuthenticatedPlayer(token))
    {
        res.status = 401;
        return;
    }

    int playerID = tokenController->getUserID(token);
    std::string roomID = req.path_params.at("roomID");
    int chatID = chatController->getChatID(roomID);
    ;
    Response response;
    if (!chatController->isChatExist(chatID))
    {
        responseController->setFailure(response, "there is no chat with this ID");
        res.set_content(responseController->getJson(response), "application/json");
        return;
    }
    if (!chatController->isPlayerInChat(chatID, playerID))
    {
        responseController->setFailure(response, "you are not in this chat");
        res.set_content(responseController->getJson(response), "application/json");
        res.status = 401;
        return;
    }
    std::thread(&ServerController::connectSocketAndLaunchSession, this, roomID, playerID).detach();
    res.set_content(responseController->success(), "application/json");
}

void ServerController::requests(httplib::Server &server)
{
    // allow cross-origin requests
    server.set_default_headers({{"Access-Control-Allow-Origin", "*"}});

    // handle preflight requests
    server.Options(R"(/.*)", [&](const httplib::Request &req, httplib::Response &res)
                   {
        res.set_header("Access-Control-Allow-Methods", "GET, PUT, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type , Authorization");
        res.status = 204; });

    server.Post("/api/register", [&](const httplib::Request &req, httplib::Response &res)
                { PostRegister(req, res); });

    server.Post("/api/login", [&](const httplib::Request &req, httplib::Response &res)
                { PostLogin(req, res); });

    server.Get("/api/info", [&](const httplib::Request &req, httplib::Response &res)
               { GetInfo(req, res); });

    server.Get("/api/admin/dashboard/:offset", [&](const httplib::Request &req, httplib::Response &res)
               { GetDashboard(req, res); });

    server.Get("/api/game/check-room/:roomID", [&](const httplib::Request &req, httplib::Response &res)
               { GetCheckRoom(req, res); });

    server.Post("/api/game/new/:type", [&](const httplib::Request &req, httplib::Response &res)
                { PostNewGame(req, res); });

    server.Post("/api/game/start/:roomID", [&](const httplib::Request &req, httplib::Response &res)
                { PostStartGame(req, res); });

    server.Get("/api/profile/personal-info", [&](const httplib::Request &req, httplib::Response &res)
               { GetProfile(req, res); });

    server.Get("/api/profile/friends", [&](const httplib::Request &req, httplib::Response &res)
               { GetFriendsProfile(req, res); });

    server.Get("/api/profile/games-info/:offset", [&](const httplib::Request &req, httplib::Response &res)
               { GetGames(req, res); });

    server.Put("/api/profile/personal-info", [&](const httplib::Request &req, httplib::Response &res)
               { PutProfile(req, res); });

    server.Get("/api/search/:query", [&](const httplib::Request &req, httplib::Response &res)
               { GetSearch(req, res); });

    server.Post("/api/add-friend/:friendID", [&](const httplib::Request &req, httplib::Response &res)
                { PostAddFriend(req, res); });

    server.Post("/api/chat/notification", [&](const httplib::Request &req, httplib::Response &res)
                { PostNotification(req, res); });

    server.Get("/api/chat/friends", [&](const httplib::Request &req, httplib::Response &res)
               { GetFriendsChat(req, res); });

    // return roomID for the chat
    server.Get("/api/chat/:chatID", [&](const httplib::Request &req, httplib::Response &res)
               { GetChat(req, res); });

    server.Get("/api/chat/room/:friendID", [&](const httplib::Request &req, httplib::Response &res)
               { GetChatRoom(req, res); });

    server.Post("/api/chat/start/:roomID", [&](const httplib::Request &req, httplib::Response &res)
                { PostStartChat(req, res); });
}

void ServerController::start(int port)
{
    httplib::Server server;
    requests(server);
    std::cout << "Server is running on port " << port << " on thread : " << std::this_thread::get_id() << std::endl;
    std::string backend_url = std::getenv("BACKEND_URL");
    server.listen(backend_url, port);
}

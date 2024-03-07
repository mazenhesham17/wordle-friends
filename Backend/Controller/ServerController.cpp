#include "ServerController.h"

ServerController *ServerController::instance = nullptr;

ServerController::ServerController()
{
    userAPI = UserAPI::getInstance();
    adminAPI = AdminAPI::getInstance();
    playerAPI = PlayerAPI::getInstance();
    authenticationController = AuthenticationController::getInstance();
    tokenController = TokenController::getInstance();
    userController = UserController::getInstance();
    socketController = SocketController::getInstance();
    responseController = ResponseController::getInstance();
    roomController = RoomController::getInstance();
}

ServerController *ServerController::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ServerController();
    }
    return instance;
}

void ServerController::connectSocketAndLaunchGameSession(const std::string &roomID, int playerID)
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
    roomController->addSession(roomID, session, playerID);
    session->launchSession();
}

void ServerController::PostRegister(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Register request of type POST received on thread : " << std::this_thread::get_id() << std::endl;

    jsoncons::json body = jsoncons::json::parse(req.body);
    User user = userController->createUser(body);
    Response response = userAPI->registerUser(user);
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::PostLogin(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Login request of type POST received on thread : " << std::this_thread::get_id() << std::endl;

    jsoncons::json body = jsoncons::json::parse(req.body);
    std::string identifier = body["identifier"].as<std::string>();
    std::string password = body["password"].as<std::string>();
    Response response = userAPI->login(identifier, password);
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::GetInfo(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Info request of type GET received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    if (!authenticationController->isAuthenticatedUser(token))
    {
        res.status = 401;
        return;
    }

    int userType = tokenController->getUserType(token);
    Response response = userAPI->info(userType);
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
    User *user = new Admin(userController->retriveUserFromDB(userID));
    Admin admin = AdminController::getInstance()->createAdmin(user);
    Response response = adminAPI->dashboard(admin);
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
    httplib::Client client("localhost", 5000);
    auto clientResponse = client.Get("/wordle");
    std::string word = jsoncons::json::parse(clientResponse->body)["word"].as<std::string>();
    Response response = playerAPI->newGame(word, playerID, gameType);
    res.set_content(responseController->getJson(response), "application/json");
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

    jsoncons::json body = jsoncons::json::parse(req.body);
    std::string roomID = body["roomID"].as<std::string>();
    if (!roomController->isRoomExist(roomID))
    {
        Response response;
        responseController->setFailure(response, "there is no room with this ID");
        res.set_content(responseController->getJson(response), "application/json");
        return;
    }
    std::thread(&ServerController::connectSocketAndLaunchGameSession, this, roomID, playerID).detach();
    res.set_content(responseController->success(), "application/json");
}

void ServerController::GetProfile(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Profile request of type GET received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    if (!authenticationController->isAuthenticatedUser(token))
    {
        res.status = 401;
        return;
    }
    int userID = tokenController->getUserID(token);
    int userType = tokenController->getUserType(token);
    User *user;
    Response response;
    if (userType == 0)
    {
        user = new Admin(userController->retriveUserFromDB(userID));
        response = adminAPI->profile(user);
    }
    else
    {
        user = new Player(userController->retriveUserFromDB(userID));
        response = playerAPI->profile(user);
    }
    res.set_content(responseController->getJson(response), "application/json");
}

void ServerController::PutProfile(const httplib::Request &req, httplib::Response &res)
{
    std::cout << "Profile request of type PUT received on thread : " << std::this_thread::get_id() << std::endl;
    std::string token = req.get_header_value("Authorization");
    if (!authenticationController->isAuthenticatedUser(token))
    {
        res.status = 401;
        return;
    }

    int userID = tokenController->getUserID(token);
    jsoncons::json body = jsoncons::json::parse(req.body);
    Response response;
    for (auto &element : body.object_range())
    {
        std::string key = element.key();
        std::string value = element.value().as<std::string>();
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

    server.Post("/register", [&](const httplib::Request &req, httplib::Response &res)
                { PostRegister(req, res); });

    server.Post("/login", [&](const httplib::Request &req, httplib::Response &res)
                { PostLogin(req, res); });

    server.Get("/info", [&](const httplib::Request &req, httplib::Response &res)
               { GetInfo(req, res); });

    server.Get("/dashboard", [&](const httplib::Request &req, httplib::Response &res)
               { GetDashboard(req, res); });

    server.Get("/check-room/:roomID", [&](const httplib::Request &req, httplib::Response &res)
               { GetCheckRoom(req, res); });

    server.Post("/new-game/:type", [&](const httplib::Request &req, httplib::Response &res)
                { PostNewGame(req, res); });

    server.Post("/start-game", [&](const httplib::Request &req, httplib::Response &res)
                { PostStartGame(req, res); });

    server.Get("/profile", [&](const httplib::Request &req, httplib::Response &res)
               { GetProfile(req, res); });

    server.Put("/profile", [&](const httplib::Request &req, httplib::Response &res)
               { PutProfile(req, res); });
}

void ServerController::start(int port)
{
    httplib::Server server;
    requests(server);
    std::cout << "Server is running on port " << port << " on thread : " << std::this_thread::get_id() << std::endl;
    server.listen("localhost", port);
}

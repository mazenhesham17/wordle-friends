#include "ServerController.h"

ServerController *ServerController::instance = nullptr;

ServerController::ServerController()
{
    userApi = UserAPI::getInstance();
    adminApi = AdminAPI::getInstance();
    playerApi = PlayerAPI::getInstance();
    tokenController = TokenController::getInstance();
    userController = UserController::getInstance();
    socketController = SocketController::getInstance();
    responseController = ResponseController::getInstance();
}

ServerController *ServerController::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ServerController();
    }
    return instance;
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
                {
            std::cout << "Request received on thread : " << std::this_thread::get_id() << std::endl;
            jsoncons::json body = jsoncons::json::parse(req.body);
            User user = userController->createUser(body);
            Response response = userApi->registerUser(user);
            res.set_content(response.getJson(), "application/json"); });

    server.Post("/login", [&](const httplib::Request &req, httplib::Response &res)
                {
            std::cout << "Request received on thread : " << std::this_thread::get_id() << std::endl;
            jsoncons::json body = jsoncons::json::parse(req.body);
            std::string identifier = body["identifier"].as<std::string>();
            std::string password = body["password"].as<std::string>();
            Response response = userApi->login(identifier, password);
            res.set_content(response.getJson(), "application/json"); });

    server.Get("/info", [&](const httplib::Request &req, httplib::Response &res)
               {
            std::cout << "Request received on thread : " << std::this_thread::get_id() << std::endl;
            std::string token = req.get_header_value("Authorization");
            if (token.empty() || !tokenController->verifyToken(token)) {
                res.status = 401;
                return;
            }
            int userType = tokenController->getUserType(token);
            Response response = userApi->info(userType);
            res.set_content(response.getJson(), "application/json"); });

    server.Get("/dashboard", [&](const httplib::Request &req, httplib::Response &res)
               {
            std::cout << "Request received on thread : " << std::this_thread::get_id() << std::endl;
            std::string token = req.get_header_value("Authorization");
            if (token.empty() || !tokenController->verifyToken(token) || !tokenController->isUserAdmin(token)) {
                res.status = 401;
                return;
            }
            int userID = tokenController->getUserID(token);
            User *user = new Admin(userController->retriveUserFromDB(userID));
            Admin admin = AdminController::getInstance()->createAdmin(user);
            Response response = adminApi->dashboard(admin);
            res.set_content(response.getJson(), "application/json"); });

    server.Post("/new-game", [&](const httplib::Request &req, httplib::Response &res)
                {
            std::cout << "Request received on thread : " << std::this_thread::get_id() << std::endl;
            std::string token = req.get_header_value("Authorization");
            if (token.empty() || !tokenController->verifyToken(token) || !tokenController->isUserPlayer(token)) {
                res.status = 401;
                return;
            }
            int playerID = tokenController->getUserID(token);
            httplib::Client client("localhost", 5000);
            auto clientResponse = client.Get("/wordle");
            std::string word = jsoncons::json::parse(clientResponse->body)["word"].as<std::string>();
            Response response = playerApi->newSingleGame(word, playerID);
            res.set_content(response.getJson(), "application/json"); });

    server.Post("/start-game", [&](const httplib::Request &req, httplib::Response &res)
                {
            std::cout << "Request received on thread : " << std::this_thread::get_id() << std::endl;
            std::string token = req.get_header_value("Authorization");
            if (token.empty() || !tokenController->verifyToken(token) || !tokenController->isUserPlayer(token)) {
                res.status = 401;
                return;
            }
            int playerID = tokenController->getUserID(token);
            std::thread(&SocketController::start, socketController,playerID).detach();
            res.set_content(R"({"message": "success"})", "application/json");
            res.status = 200; });

    server.Get("/profile", [&](const httplib::Request &req, httplib::Response &res)
               {
            std::cout << "Request received on thread : " << std::this_thread::get_id() << std::endl;
            std::string token = req.get_header_value("Authorization");
            if (token.empty() || !tokenController->verifyToken(token)) {
                res.status = 401;
                return;
            }
            int userID = tokenController->getUserID(token);
            int userType = tokenController->getUserType(token);
            User *user ;
            Response response;
            if (userType == 0) {
                user = new Admin(userController->retriveUserFromDB(userID));
                response = adminApi->profile(user);
            } else {
                user = new Player(userController->retriveUserFromDB(userID));
                response = playerApi->profile(user);
            }
            res.set_content(response.getJson(), "application/json"); });

    server.Put("/profile", [&](const httplib::Request &req, httplib::Response &res)
               {
        std::cout << "Request received on thread : " << std::this_thread::get_id() << std::endl;
        std::string token = req.get_header_value("Authorization");
        if (token.empty() || !tokenController->verifyToken(token)) {
            res.status = 401;
            return;
        }
        int userID = tokenController->getUserID(token);
        jsoncons::json body = jsoncons::json::parse(req.body);
        Response response;
        for ( auto & element : body.object_range()){
            std::string key = element.key();
            std::string value = element.value().as<std::string>();
            response = playerApi->updatePlayer(userID,key,value);
            // there is a field that is not updated
            if ( !responseController->isSuccess(response) ) {
                res.set_content(response.getJson(), "application/json");
                return;
            }
        }
        res.set_content(response.getJson(), "application/json"); });
}

void ServerController::start()
{
    httplib::Server server;
    requests(server);
    std::cout << "Server is running on port 4000 on thread : " << std::this_thread::get_id() << std::endl;
    server.listen("localhost", 4000);
}
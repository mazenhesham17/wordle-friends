#include "ServerController.h"

ServerController *ServerController::instance = nullptr;

ServerController::ServerController()
{
    userApi = UserAPI::getInstance();
    adminApi = AdminAPI::getInstance();
    playerApi = PlayerAPI::getInstance();
    tokenController = TokenController::getInstance();
    userController = UserController::getInstance();
}

ServerController *ServerController::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ServerController();
    }
    return instance;
}

void ServerController::requests()
{
    // allow cross-origin requests
    server.set_default_headers({{"Access-Control-Allow-Origin", "*"}});

    // handle preflight requests
    server.Options(R"(/.*)", [&](const httplib::Request &req, httplib::Response &res)
                   {
            res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type , Authorization");
            res.status = 204; });

    server.Post("/register", [&](const httplib::Request &req, httplib::Response &res)
                {
            jsoncons::json body = jsoncons::json::parse(req.body);
            User user = userController->createUser(body);
            Response response = userApi->registerUser(user);
            res.set_content(response.getJson(), "application/json"); });

    server.Post("/login", [&](const httplib::Request &req, httplib::Response &res)
                {
            jsoncons::json body = jsoncons::json::parse(req.body);
            std::string identifier = body["identifier"].as<std::string>();
            std::string password = body["password"].as<std::string>();
            Response response = userApi->login(identifier, password);
            res.set_content(response.getJson(), "application/json"); });

    server.Post("/new-game", [&](const httplib::Request &req, httplib::Response &res)
                {
            std::string token = req.get_header_value("Authorization");
            if (token.empty() || !tokenController->verifyToken(token) || !tokenController->isUserPlayer(token)) {
                res.status = 401;
                return;
            }
            httplib::Client client("localhost", 5000);
            auto clientResponse = client.Get("/wordle");
            jsoncons::json body = jsoncons::json::parse(clientResponse->body);
            Response response = userApi->newSingleGame(token, body["word"].as<std::string>());
            res.set_content(response.getJson(), "application/json"); });

    server.Get("/profile", [&](const httplib::Request &req, httplib::Response &res)
               {
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
}

void ServerController::start(int port)
{
    server.listen("localhost", port);
}
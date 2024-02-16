#include <iostream>
#include <httplib.h>
#include <jsoncons/json.hpp>
#include "Database/dml.h"
#include "Database/constants.h"
#include "Controller/TokenController.h"
#include "Controller/UserController.h"
#include "Model/User.h"
#include "API/UserAPI.h"
#include "API/AdminAPI.h"
#include "API/PlayerAPI.h"

const int QUERY_SIZE = 1024;
const int ERROR_SIZE = 1024;
const char *DATABASE_FILE_NAME = "wordle_data.db";
const std::string SECRET_KEY = "94e5ec91cb8779e0cc5fff2e0fdf2f0362e7a5d9e56205e02677173bbc8b0835";
sqlite3 *db;

int main()
{
    try
    {
        openConnection();
        httplib::Server server;
        httplib::Client client("localhost", 5000);
        UserAPI *userApi = UserAPI::getInstance();
        AdminAPI *adminApi = AdminAPI::getInstance();
        PlayerAPI *playerApi = PlayerAPI::getInstance();
        TokenController *tokenController = TokenController::getInstance();
        UserController *userController = UserController::getInstance();
        Admin *admin = nullptr;
        Player *player = nullptr;

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
            auto clientResponse = client.Get("/wordle");
            jsoncons::json body = jsoncons::json::parse(clientResponse->body);
            Response response = userApi->newSingleGame(token, body["word"].as<std::string>());
            res.set_content(response.getJson(), "application/json"); });

        server.Get("/profile", [&](const httplib::Request &req, httplib::Response &res)
                   {
            std::string token = req.get_header_value("Authorization");
            std::cout << "Before token verification" << std::endl;
            if (token.empty() || !tokenController->verifyToken(token)) {
                res.status = 401;
                return;
            }
            int userID = tokenController->getUserID(token);
            int userType = tokenController->getUserType(token);
            User user = userController->retriveUserFromDB(userID);
            Response response;
            if (userType == 0) {
                admin = reinterpret_cast<Admin *>(&user);
                response = adminApi->profile(*admin);
            } else {
                player = reinterpret_cast<Player *>(&user);
                response = playerApi->profile(*player);
            }
            res.set_content(response.getJson(), "application/json"); });
        server.listen("localhost", 4000);
        //        int t = addTournament(1);
        //        addPlayerToTournament(a, t);
        //        addPlayerToTournament(b, t);
        //        int g = addGame("wordle");
        //        addPlayerToGame(a, g);
        //        addPlayerToGame(b, g);
        //        addGameToTournament(t, g, 1);
        //        winGame(b, g);
        //        winTournament(b, t);
        //        int c = addChat();
        //        addPlayerToChat(a, c);
        //        addPlayerToChat(b, c);
        //        addMessageToChat(a, c, "Hello Hazem");
        //        addMessageToChat(b, c, "Hello Mazen");
        //        changeFirstName(2,"mazen") ;
        //        changeLastName(3,"adel") ;
        //        changeEmail(1,"admin@lgh.com") ;
        //        changePassword(2,"hello") ;
        //        deleteTournament(1) ;
        //        deleteGame(1) ;
        closeConnection();
    }
    catch (std::exception &error)
    {
        std::cerr << error.what() << std::endl;
    }
    return 0;
}

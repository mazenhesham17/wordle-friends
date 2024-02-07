#include <iostream>
#include <httplib.h>
#include <jsoncons/json.hpp>
#include <jwt-cpp/jwt.h>
#include "Database/dml.h"
#include "Database/dql.h"
#include "Database/constants.h"
#include "API/UserAPI.h"

const int QUERY_SIZE = 1024;
const int ERROR_SIZE = 1024;
const char *DATABASE_FILE_NAME = "wordle_data.db";
const std::string SECRET_KEY = "94e5ec91cb8779e0cc5fff2e0fdf2f0362e7a5d9e56205e02677173bbc8b0835";
sqlite3 *db;

using namespace jwt;

int main()
{
    try
    {
        openConnection();

        httplib::Server server;
        UserAPI *userApi = UserAPI::getInstance();

        // allow cross-origin requests
        server.set_default_headers({{"Access-Control-Allow-Origin", "*"}});

        // handle preflight requests
        server.Options(R"(/.*)", [&](const httplib::Request &req, httplib::Response &res)
                       {
            res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type , Authorization");
            res.status = 204; });

        server.Post("/login", [&](const httplib::Request &req, httplib::Response &res)
                    {
            jsoncons::json body = jsoncons::json::parse(req.body);
            std::string identifier = body["identifier"].as<std::string>();
            std::string password = body["password"].as<std::string>() ;
            Response response = userApi->login(identifier,password) ;
            res.set_content(response.getJson(), "application/json"); });

        server.Post("/register", [&](const httplib::Request &req, httplib::Response &res)
                    {
            jsoncons::json body = jsoncons::json::parse(req.body);
            std::string username = body["username"].as<std::string>();
            std::string firstName = body["firstName"].as<std::string>();
            std::string lastName = body["lastName"].as<std::string>();
            std::string email = body["email"].as<std::string>();
            std::string password = body["password"].as<std::string>();
            Response response = userApi->registerUser(username,firstName,lastName,email,password) ;
            res.set_content(response.getJson(), "application/json"); });

        server.Get("/profile", [&](const httplib::Request &req, httplib::Response &res)
                   {
            std::string token = req.get_header_value("Authorization");
            if (token.empty())
            {
                res.status = 401;
                return;
            }
            Response response = userApi->profile(token);
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

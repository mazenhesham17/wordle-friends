#include <iostream>
#include <httplib.h>
#include <jsoncons/json.hpp>
#include "Database/dml.h"
#include "Database/constants.h"
#include "Controller/TokenController.h"
#include "Controller/UserController.h"
#include "Controller/ServerController.h"
#include "Model/User.h"
#include "Model/Admin.h"
#include "Model/Player.h"
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
        ServerController *serverController = ServerController::getInstance();
        serverController->requests();
        serverController->start(4000);

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

#include <iostream>
#include "Controller/ServerController.h"
#include "Database/dml.h"
#include "Database/constants.h"

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
        serverController->start();
        //        int c = addChat();
        //        addPlayerToChat(a, c);
        //        addPlayerToChat(b, c);
        //        addMessageToChat(a, c, "Hello Hazem");
        //        addMessageToChat(b, c, "Hello Mazen");
        closeConnection();
    }
    catch (std::exception &error)
    {
        std::cerr << error.what() << std::endl;
    }
    return 0;
}

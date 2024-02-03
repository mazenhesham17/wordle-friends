#include <iostream>
#include "Database/dml.h"
#include "Database/constants.h"

const int QUERY_SIZE = 1024;
const int ERROR_SIZE = 1024;
const char *DATABASE_FILE_NAME = "wordle_data.db";
sqlite3 *db;

int main() {
    try {
        openConnection();
//        int a = addPlayer("mazen", "m", "h", "m@lgh.com", "123");
//        int b = addPlayer("hazem", "h", "a", "h@siemens.com", "123");
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
    } catch (std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
    return 0;
}

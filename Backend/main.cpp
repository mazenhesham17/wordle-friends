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
        int a = addPlayer("mazen", "m", "h", "m@lgh.com", "123");
        int b = addPlayer("hazem", "h", "a", "h@siemens.com", "123");
        int t = addTournament(1);
        addPlayerToTournament(a, t);
        addPlayerToTournament(b, t);
        int g = addGame("wordle");
        addPlayerToGame(a, g);
        addPlayerToGame(b, g);
        addGameToTournament(t, g, 1);
        winGame(b, g);
        winTournament(b, t);
        int c = addChat();
        addPlayerToChat(a, c);
        addPlayerToChat(b, c);
        addMessageToChat(a, c, "Hello Hazem");
        addMessageToChat(b, c, "Hello Mazen");
        closeConnection();
    } catch (std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
    return 0;
}

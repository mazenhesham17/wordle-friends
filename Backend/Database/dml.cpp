#include <iostream>
#include <sqlite3.h>
#include "dml.h"
#include "constants.h"


bool openConnection() {
    int resultCode = sqlite3_open(DATABASE_FILE_NAME, &db);
    if (resultCode != SQLITE_OK) {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error opening %s.\nError: %s ",
                 DATABASE_FILE_NAME, sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }
    return true;
}

int addPlayer(const char *username, const char *firstName, const char *lastName, const char *email,
              const char *password) {
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO User (username, firstName, lastName, email, password, userType)
                VALUES ('%s','%s','%s','%s','%s',1); )",
             username, firstName, lastName, email, password);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK) {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error registering the player.\nError: %s", sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // retrieve registered player ID
    int playerID = static_cast<int>(sqlite3_last_insert_rowid(db));

    // free memory
    sqlite3_free(sqlError);
    return playerID;
}

int addGame(const char *word) {
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO Game (word) VALUES ('%s'); )", word);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK) {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error creating a game.\nError: %s", sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // retrieve created game ID
    int gameID = static_cast<int>(sqlite3_last_insert_rowid(db));

    // free memory
    sqlite3_free(sqlError);
    return gameID;
}

bool addPlayerToGame(int playerID, int gameID) {
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO GamePlayers VALUES (%d,%d); )", gameID, playerID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK) {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error adding player #%d to game #%d.\nError: %s", playerID, gameID, sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}

int addTournament(int adminID) {
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO Tournament (adminID) VALUES (%d); )", adminID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK) {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error creating a tournament.\nError: %s", sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // retrieve created tournament ID
    int tournamentID = static_cast<int>(sqlite3_last_insert_rowid(db));

    // free memory
    sqlite3_free(sqlError);
    return tournamentID;
}

bool addPlayerToTournament(int playerID, int tournamentID) {
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO TournamentPlayers VALUES (%d,%d); )", tournamentID, playerID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK) {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error adding player #%d to tournament #%d.\nError: %s", playerID, tournamentID,
                 sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}

bool addGameToTournament(int tournamentID, int gameID, int stage) {
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO TournamentGames VALUES (%d,%d,%d); )", tournamentID, gameID, stage);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK) {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error adding game #%d to tournament #%d.\nError: %s", gameID, tournamentID,
                 sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}


int addChat() {
    // prepare query
    char query[] = "INSERT INTO Chat (chatID) VALUES (NULL);";

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK) {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error creating a chat.\nError: %s", sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // retrieve created chat ID
    int chatID = static_cast<int>(sqlite3_last_insert_rowid(db));

    // free memory
    sqlite3_free(sqlError);
    return chatID;
}

bool addPlayerToChat(int playerID, int chatID) {
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO PlayerChats VALUES (%d,%d); )", playerID, chatID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK) {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error adding player #%d to chat #%d.\nError: %s", playerID, chatID, sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}

bool addMessageToChat(int senderID, int chatID, const char *content) {
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO Message (senderID,content,chatID) VALUES (%d,'%s',%d); )", senderID, content, chatID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK) {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error adding message to chat #%d.\nError: %s", chatID, sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}

bool winTournament(int playerID, int tournamentID) {
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( UPDATE Tournament SET winnerID = %d WHERE tournamentID = %d ; )", playerID, tournamentID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK) {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error winning tournament #%d with player #%d.\nError: %s", tournamentID, playerID,
                 sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}

bool winGame(int playerID, int gameID) {
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( UPDATE Game SET winnerID = %d WHERE gameID = %d ; )", playerID, gameID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK) {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error winning game #%d with player #%d.\nError: %s", gameID, playerID, sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}

bool closeConnection() {
    int resultCode = sqlite3_close(db);
    if (resultCode != SQLITE_OK) {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error closing %s.\nError: %s",
                 DATABASE_FILE_NAME, sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }
    return true;
}



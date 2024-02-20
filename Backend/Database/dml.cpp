#include "dml.h"

bool openConnection()
{
    int resultCode = sqlite3_open(DATABASE_FILE_NAME, &db);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error opening %s.\nError: %s ",
                 DATABASE_FILE_NAME, sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }
    // enable foreign key
    const char *foreignKey = "PRAGMA foreign_keys = ON;";

    // execute query
    sqlite3_exec(db, foreignKey, nullptr, nullptr, nullptr);
    return true;
}

int addPlayer(const char *username, const char *firstName, const char *lastName, const char *email,
              const char *password)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO User (username, firstName, lastName, email, password, userType)
                VALUES ('%s','%s','%s','%s','%s',1); )",
             username, firstName, lastName, email, password);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
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

int addGame(const char *word)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO Game (word,state) VALUES ('%s',0); )", word);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
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

bool addPlayerToGame(int playerID, int gameID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO GamePlayers VALUES (%d,%d); )", gameID, playerID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
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

bool dbStartGame(int gameID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( UPDATE Game SET state = 1 WHERE gameID = %d ; )", gameID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error starting game #%d.\nError: %s", gameID, sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}

bool dbEndGame(int gameID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( UPDATE Game SET state = 2 WHERE gameID = %d ; )", gameID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error ending game #%d.\nError: %s", gameID, sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}

int addTournament(int adminID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO Tournament (adminID) VALUES (%d); )", adminID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
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

bool addPlayerToTournament(int playerID, int tournamentID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO TournamentPlayers VALUES (%d,%d); )", tournamentID, playerID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
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

bool addGameToTournament(int tournamentID, int gameID, int stage)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO TournamentGames VALUES (%d,%d,%d); )", tournamentID, gameID, stage);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
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

int addChat()
{
    // prepare query
    char query[] = "INSERT INTO Chat (chatID) VALUES (NULL);";

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
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

bool addPlayerToChat(int playerID, int chatID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO PlayerChats VALUES (%d,%d); )", playerID, chatID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
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

bool addMessageToChat(int senderID, int chatID, const char *content)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( INSERT INTO Message (senderID,content,chatID) VALUES (%d,'%s',%d); )", senderID, content, chatID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
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

bool winTournament(int playerID, int tournamentID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( UPDATE Tournament SET winnerID = %d WHERE tournamentID = %d ; )", playerID, tournamentID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
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

bool dbWinGame(int playerID, int gameID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( UPDATE Game SET winnerID = %d , state = 2 WHERE gameID = %d ; )", playerID, gameID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
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

bool changeFirstName(int userID, const char *firstName)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( UPDATE User SET firstName = '%s' WHERE userID = %d ; )", firstName, userID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error changing first name for user #%d.\nError: %s", userID, sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}

bool changeLastName(int userID, const char *lastName)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( UPDATE User SET lastName = '%s' WHERE userID = %d ; )", lastName, userID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error changing last name for user #%d.\nError: %s", userID, sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}

bool changeEmail(int userID, const char *email)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( UPDATE User SET email = '%s' WHERE userID = %d ; )", email, userID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error changing email for user #%d.\nError: %s", userID, sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}

bool changePassword(int userID, const char *password)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( UPDATE User SET password = '%s' WHERE userID = %d ; )", password, userID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error changing password for user #%d.\nError: %s", userID, sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}

bool deleteTournament(int tournamentID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( DELETE FROM Tournament WHERE tournamentID = %d ; )", tournamentID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error removing tournament #%d.\nError: %s", tournamentID, sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}

bool deleteGame(int gameID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( DELETE FROM Game WHERE gameID = %d ; )", gameID);

    // execute query
    char *sqlError;
    int resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error removing game #%d.\nError: %s", gameID, sqlError);

        // free memory
        sqlite3_free(sqlError);
        throw std::runtime_error(errorMessage);
    }

    // free memory
    sqlite3_free(sqlError);
    return true;
}

bool closeConnection()
{
    int resultCode = sqlite3_close(db);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 "There was an error closing %s.\nError: %s",
                 DATABASE_FILE_NAME, sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }
    return true;
}

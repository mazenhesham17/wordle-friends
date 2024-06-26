#include <iostream>
#include <sqlite3.h>

const char *DATABASE_FILE_NAME = "wordle_data.db";
sqlite3 *db;

int main()
{
    int resultCode;

    auto executeQuery = [&](const char *query, const char *customError)
    {
        char *sqlError;
        resultCode = sqlite3_exec(db, query, nullptr, nullptr, &sqlError);
        if (resultCode != SQLITE_OK)
        {
            std::cerr << "There was an error creating user table." << std::endl;
            std::cerr << "Error Message : " << sqlError << std::endl;
            sqlite3_free(sqlError);
            return resultCode;
        }
        sqlite3_free(sqlError);
        return SQLITE_OK;
    };

    // opening the database connection
    resultCode = sqlite3_open(DATABASE_FILE_NAME, &db);
    if (resultCode != SQLITE_OK)
    {
        std::cerr << "There was an error opening " << DATABASE_FILE_NAME << "." << std::endl;
        return resultCode;
    }

    // enable foreign key constrain

    // query
    const char *foreignKey = "PRAGMA foreign_keys = ON;";

    // execution
    resultCode = executeQuery(foreignKey,
                              "There was an error enabling foreign key constrain.");
    if (resultCode != SQLITE_OK)
    {
        return resultCode;
    }

    // create user table

    // query
    const char *userTableCreation = R"(
        CREATE TABLE IF NOT EXISTS User(
	        userID INTEGER UNIQUE PRIMARY KEY,
  	        username TEXT UNIQUE,
  	        firstName TEXT,
  	        lastName TEXT,
  	        email TEXT,
  	        password TEXT,
  	        userType INTEGER,
            joinTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        );
    )";

    // execution
    resultCode = executeQuery(userTableCreation,
                              "There was an error creating user table.");
    if (resultCode != SQLITE_OK)
    {
        return resultCode;
    }

    // create friends table

    // query

    const char *friendsTableCreation = R"(
        CREATE TABLE IF NOT EXISTS Friends(
  	        senderID INTEGER,
  	        acceptorID INTEGER,
  	        PRIMARY KEY (senderID,acceptorID),
  	        FOREIGN KEY (senderID) REFERENCES User(userID) ON DELETE CASCADE,
  	        FOREIGN KEY (acceptorID) REFERENCES User(userID) ON DELETE CASCADE
        );
    )";

    // execution

    resultCode = executeQuery(friendsTableCreation,
                              "There was an error creating friends table.");
    if (resultCode != SQLITE_OK)
    {
        return resultCode;
    }

    // create game table

    // query
    const char *gameTableCreation = R"(
        CREATE TABLE IF NOT EXISTS Game(
  	        gameID INTEGER UNIQUE PRIMARY KEY,
  	        word TEXT,
            state INTEGER,
  	        winnerID INTEGER,
            createTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  	        FOREIGN KEY (winnerID) REFERENCES User(userid)
        );
    )";

    // execution
    resultCode = executeQuery(gameTableCreation,
                              "There was an error creating game table.");
    if (resultCode != SQLITE_OK)
    {
        return resultCode;
    }

    // create chat table

    // query
    const char *chatTableCreation = R"(
        CREATE TABLE IF NOT EXISTS Chat(
  	        chatID INTEGER UNIQUE PRIMARY KEY
        );
    )";

    // execution
    resultCode = executeQuery(chatTableCreation,
                              "There was an error creating chat table.");
    if (resultCode != SQLITE_OK)
    {
        return resultCode;
    }

    // create game players table

    // query
    const char *gamePlayersTableCreation = R"(
        CREATE TABLE IF NOT EXISTS GamePlayers(
	        gameID INTEGER,
  	        playerID INTEGER,
            PRIMARY KEY (gameID,playerID),
            FOREIGN KEY (gameID) REFERENCES Game(gameID) ON DELETE CASCADE,
            FOREIGN KEY (playerID) REFERENCES User(userID)
        );
    )";

    // execution
    resultCode = executeQuery(gamePlayersTableCreation,
                              "There was an error creating game players table.");
    if (resultCode != SQLITE_OK)
    {
        return resultCode;
    }

    // create player chats table

    // query
    const char *playerChatsTableCreation = R"(
        CREATE TABLE If NOT EXISTS PlayerChats(
            playerID INTEGER,
            chatID INTEGER,
            PRIMARY KEY (playerID,chatID),
            FOREIGN KEY (playerID) REFERENCES User(userID),
            FOREIGN KEY (chatID) REFERENCES Chat(chatID)
        );
    )";

    // execution
    resultCode = executeQuery(playerChatsTableCreation,
                              "There was an error creating player chats table.");
    if (resultCode != SQLITE_OK)
    {
        return resultCode;
    }

    // create message table

    // query
    const char *messageTableCreation = R"(
        CREATE TABLE IF NOT EXISTS Message(
            messageID INTEGER UNIQUE PRIMARY KEY,
            content TEXT,
            senderID INTEGER,
            dateAndTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            chatID INTEGER,
            readStatus INTEGER DEFAULT 0,
            FOREIGN KEY (senderID) REFERENCES User(userID),
            FOREIGN KEY (chatID) REFERENCES Chat(chatID)
        );
    )";

    // execution
    resultCode = executeQuery(messageTableCreation,
                              "There was an error creating message table.");
    if (resultCode != SQLITE_OK)
    {
        return resultCode;
    }

    // insert admin

    // query
    const char *insertAdminUser = R"(
        INSERT INTO User (username, firstName, lastName, email, password, userType)
        VALUES ('admin','','', 'admin@wordle.com', '8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918', 0);
    )";

    // execution
    resultCode = executeQuery(insertAdminUser,
                              "There was an error inserting admin account.");
    if (resultCode != SQLITE_OK)
    {
        return resultCode;
    }

    // closing the database connection
    resultCode = sqlite3_close(db);
    if (resultCode != SQLITE_OK)
    {
        std::cerr << "There was an error closing " << DATABASE_FILE_NAME << "." << std::endl;
        return resultCode;
    }
    return 0;
}

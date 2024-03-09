#ifndef BACKEND_DML_H
#define BACKEND_DML_H

#include <iostream>
#include <sqlite3.h>
#include "constants.h"

// open database connection
bool openConnection();

// add new user
int addPlayer(const char *username, const char *firstName, const char *lastName, const char *email,
              const char *password);

// add new friend
bool dbAddFriend(int playerID, int friendID);

// add new game
int addGame(const char *word);

// add player to game
bool addPlayerToGame(int playerID, int gameID);

// start game
bool dbStartGame(int gameID);

// end game
bool dbEndGame(int gameID);

// add new chat
int dbAddChat();

// add player to chat
bool addPlayerToChat(int playerID, int chatID);

// add message to chat
int addMessageToChat(int senderID, int chatID, const char *content);

// win game
bool dbWinGame(int playerID, int gameID);

// update user field
bool updatePlayerField(int userID, const char *field, const char *value);

// remove game
bool dbDeleteGame(int gameID);

// close database connection
bool closeConnection();

#endif // BACKEND_DML_H

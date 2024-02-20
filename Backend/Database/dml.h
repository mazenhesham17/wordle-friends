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

// add new game
int addGame(const char *word);

// add player to game
bool addPlayerToGame(int playerID, int gameID);

// start game
bool startNewGame(int gameID);

// add new tournament
int addTournament(int adminID);

// add player to tournament
bool addPlayerToTournament(int playerID, int tournamentID);

// add game to tournament
bool addGameToTournament(int tournamentID, int gameID, int stage);

// add new chat
int addChat();

// add player to chat
bool addPlayerToChat(int playerID, int chatID);

// add message to chat
bool addMessageToChat(int senderID, int chatID, const char *content);

// win game
bool winGame(int playerID, int gameID);

// win tournament
bool winTournament(int playerID, int tournamentID);

// update the first name
bool changeFirstName(int userID, const char *firstName);

// update the last name
bool changeLastName(int userID, const char *lastName);

// update the email
bool changeEmail(int userID, const char *email);

// update the password
bool changePassword(int userID, const char *password);

// remove tournament
bool deleteTournament(int tournamentID);

// remove game
bool deleteGame(int gameID);

// close database connection
bool closeConnection();


#endif //BACKEND_DML_H

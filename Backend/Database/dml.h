#ifndef BACKEND_DML_H
#define BACKEND_DML_H

// open database connection
bool openConnection();

// add new user
int addPlayer(const char *username, const char *firstName, const char *lastName, const char *email,
              const char *password);

// add new game
int addGame(const char *word);

// add player to game
bool addPlayerToGame(int playerID, int gameID);

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

// close database connection
bool closeConnection();


#endif //BACKEND_DML_H

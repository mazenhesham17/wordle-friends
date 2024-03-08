#ifndef BACKEND_DQL_H
#define BACKEND_DQL_H

#include <iostream>
#include <cstring>
#include <vector>
#include <sqlite3.h>
#include "constants.h"

int checkPasswordByUsername(const std::string &username, const std::string &password);

int checkPasswordByEmailAddress(const std::string &email, const std::string &password);

int getUserIDByUsername(const std::string &username);

int getUserIDByEmailAddress(const std::string &email);

int getUserTypeByUserID(int userID);

std::string getEmailByUserID(int userID);

std::string getFirstNameByUserID(int userID);

std::string getLastNameByUserID(int userID);

std::string getUsernameByUserID(int userID);

std::string getWordByGameID(int gameID);

std::vector<int> getFriendListByUserID(int userID);

std::vector<int> getPlayersListByPartialUsername(const std::string &partialUsername);

int getGamesCountByUserID(int userID);

int getWinsCountByUserID(int userID);

int getTotalGamesCount();

int getTotalWinsCount();

int getTotalPlayersCount();

bool isUsernameExist(const std::string &username);

bool isEmailExist(const std::string &email);

bool isUserExist(int userID);

bool dbIsFriend(int userID, int freindID);

bool dbIsPlayerInGame(const int &playerID);

#endif // BACKEND_DQL_H

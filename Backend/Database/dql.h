#ifndef BACKEND_DQL_H
#define BACKEND_DQL_H

#include <iostream>
#include <cstring>
#include <vector>
#include <tuple>
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

std::string getContentByMessageID(int messageID);

std::string getSendTimeByMessageID(int messageID);

int getSenderIDByMessageID(int messageID);

int getChatIDByMessageID(int messageID);

int getChatIDByPlayerID(int playerID, int friendID);

std::vector<int> getChatListByChatID(int chatID);

std::vector<int> getFriendListByUserID(int userID);

std::vector<int> getOrderedFriendListByUserID(int userID);

std::vector<int> getPlayersListByPartialUsername(const std::string &partialUsername);

std::vector<int> getPlayersListByChatID(int chatID);

std::vector<std::tuple<std::string, int, int>> getGamesByUserID(int userID, int offset);

std::vector<std::tuple<std::string, int, int>> getAllGames(int offset);

std::vector<std::tuple<std::string, int>> getAllMessages(int offset);

std::vector<std::tuple<std::string, int>> getAllPlayers(int offset);

int getLastMessageStatusByUsersID(int playerID, int friendID);

int getGamesCountByUserID(int userID);

int getWinsCountByUserID(int userID);

int getTotalGamesCount();

int getTotalWinsCount();

int getTotalPlayersCount();

bool dbIsUsernameExist(const std::string &username);

bool dbIsEmailExist(const std::string &email);

bool isUserExist(int userID);

bool dbIsPlayerInChat(int chatID, int playerID);

bool dbIsFriend(int userID, int freindID);

bool dbIsPlayerInGame(const int &playerID);

bool dbIsChatExist(const int &chatID);

#endif // BACKEND_DQL_H

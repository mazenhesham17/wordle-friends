#ifndef BACKEND_DQL_H
#define BACKEND_DQL_H

int checkPasswordByUsername(const std::string &username, const std::string &password);

int checkPasswordByEmailAddress(const std::string &email, const std::string &password);

int getUserTypeByUserID(int userID);

std::string getUsernameByUserID(int userID);

#endif // BACKEND_DQL_H

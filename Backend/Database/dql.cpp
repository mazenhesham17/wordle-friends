#include <iostream>
#include <cstring>
#include <sqlite3.h>
#include "dql.h"
#include "constants.h"

int checkPasswordByUsername(const std::string &username, const std::string &password)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( SELECT password FROM User WHERE username = '%s')", username.c_str());

    // prepare statement
    sqlite3_stmt *stmt;
    int resultCode = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 R"(There was an error checking for password.\n
                    Error: %s )",
                 sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }

    std::string retrivedPassword;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char *temp = const_cast<char *>(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        retrivedPassword = temp;
    }
    else if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        return -1; // User not found
    }
    sqlite3_finalize(stmt);

    if (password == retrivedPassword)
    {
        return 1; // Password is correct
    }
    else
    {
        return 0; // Password is incorrect
    }
}

int checkPasswordByEmailAddress(const std::string &email, const std::string &password)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( SELECT password FROM User WHERE email = '%s')", email.c_str());

    // prepare statement
    sqlite3_stmt *stmt;
    int resultCode = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 R"(There was an error checking for password.\n
                    Error: %s )",
                 sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }

    std::string retrivedPassword;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char *temp = const_cast<char *>(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        retrivedPassword = temp;
    }
    else if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        return -1; // User not found
    }
    sqlite3_finalize(stmt);

    if (password == retrivedPassword)
    {
        return 1; // Password is correct
    }
    else
    {
        return 0; // Password is incorrect
    }
}

int getUserTypeByUserID(int userID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( SELECT userType FROM User WHERE userID = %d)", userID);

    // prepare statement
    sqlite3_stmt *stmt;
    int resultCode = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 R"(There was an error checking for user type.\n
                    Error: %s )",
                 sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }

    int userType = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        userType = sqlite3_column_int(stmt, 0);
    }
    else if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        return -1; // User not found
    }
    sqlite3_finalize(stmt);

    return userType;
}

std::string getUsernameByUserID(int userID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( SELECT username FROM User WHERE userID = %d)", userID);

    // prepare statement
    sqlite3_stmt *stmt;
    int resultCode = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 R"(There was an error checking for username.\n
                    Error: %s )",
                 sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }

    std::string username;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char *temp = const_cast<char *>(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        username = temp;
    }
    else if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        return "not found"; // User not found
    }
    sqlite3_finalize(stmt);

    return username;
}
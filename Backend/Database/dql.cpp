#include "dql.h"


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
        return getUserIDByUsername(username); // Password is correct
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
        return getUserIDByEmailAddress(email); // Password is correct
    }
    else
    {
        return 0; // Password is incorrect
    }
}

int getUserIDByUsername(const std::string &username)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( SELECT userID FROM User WHERE username = '%s')", username.c_str());

    // prepare statement
    sqlite3_stmt *stmt;
    int resultCode = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 R"(There was an error checking for userID.\n
                    Error: %s )",
                 sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }

    int userID = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        userID = sqlite3_column_int(stmt, 0);
    }
    else if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        return -1; // User not found
    }
    sqlite3_finalize(stmt);

    return userID;
}

int getUserIDByEmailAddress(const std::string &email)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( SELECT userID FROM User WHERE email = '%s')", email.c_str());

    // prepare statement
    sqlite3_stmt *stmt;
    int resultCode = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 R"(There was an error checking for userID.\n
                    Error: %s )",
                 sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }

    int userID = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        userID = sqlite3_column_int(stmt, 0);
    }
    else if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        return -1; // User not found
    }
    sqlite3_finalize(stmt);

    return userID;
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
                 R"(There was an error getting username.\n
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

std::string getEmailByUserID(int userID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( SELECT email FROM User WHERE userID = %d)", userID);

    // prepare statement
    sqlite3_stmt *stmt;
    int resultCode = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 R"(There was an error getting for email.\n
                    Error: %s )",
                 sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }

    std::string email;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char *temp = const_cast<char *>(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        email = temp;
    }
    else if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        return "not found"; // User not found
    }
    sqlite3_finalize(stmt);

    return email;
}

std::string getFirstNameByUserID(int userID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( SELECT firstName FROM User WHERE userID = %d)", userID);

    // prepare statement
    sqlite3_stmt *stmt;
    int resultCode = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 R"(There was an error getting for first name.\n
                    Error: %s )",
                 sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }

    std::string firstName;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char *temp = const_cast<char *>(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        firstName = temp;
    }
    else if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        return "not found"; // User not found
    }
    sqlite3_finalize(stmt);

    return firstName;
}

std::string getLastNameByUserID(int userID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( SELECT lastName FROM User WHERE userID = %d)", userID);

    // prepare statement
    sqlite3_stmt *stmt;
    int resultCode = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 R"(There was an error getting for last name.\n
                    Error: %s )",
                 sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }

    std::string lastName;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char *temp = const_cast<char *>(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        lastName = temp;
    }
    else if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        return "not found"; // User not found
    }
    sqlite3_finalize(stmt);

    return lastName;
}

std::string getWordByGameID(int gameID)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( SELECT word FROM Game WHERE gameID = %d)", gameID);

    // prepare statement
    sqlite3_stmt *stmt;
    int resultCode = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 R"(There was an error getting for word.\n
                    Error: %s )",
                 sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }

    std::string word;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char *temp = const_cast<char *>(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0)));
        word = temp;
    }
    else if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        return "not found"; // Game not found
    }
    sqlite3_finalize(stmt);

    return word;
}

bool isUsernameExist(const std::string &username)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( SELECT username FROM User WHERE username = '%s')", username.c_str());

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

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        return true;
    }
    else if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return false;
    }
    return false;
}

bool isEmailExist(const std::string &email)
{
    // prepare query
    char query[QUERY_SIZE];
    snprintf(query, sizeof(query),
             R"( SELECT email FROM User WHERE email = '%s')", email.c_str());

    // prepare statement
    sqlite3_stmt *stmt;
    int resultCode = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (resultCode != SQLITE_OK)
    {
        char errorMessage[ERROR_SIZE];
        snprintf(errorMessage, sizeof(errorMessage),
                 R"(There was an error checking for email.\n
                    Error: %s )",
                 sqlite3_errmsg(db));
        throw std::runtime_error(errorMessage);
    }

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        return true;
    }
    else if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return false;
    }
    return false;
}

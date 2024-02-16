#ifndef BACKEND_USER_H
#define BACKEND_USER_H

#include <string>

class User
{
    int userID;
    int userType;
    std::string username;
    std::string password;
    std::string email;
    std::string firstName;
    std::string lastName;

public:
    User() = default;

    User(int userID, int user);

    User(int userID, int user, std::string username, std::string password, std::string email, std::string firstName,
         std::string lastName);

    int getUserID() const;

    void setUserID(int userID);

    int getUserType() const;

    void setUserType(int userType);

    std::string getUsername() const;

    void setUsername(const std::string &username);

    std::string getPassword() const;

    void setPassword(const std::string &password);

    std::string getEmail() const;

    void setEmail(const std::string &email);

    std::string getFirstName() const;

    void setFirstName(const std::string &firstName);

    std::string getLastName() const;

    void setLastName(const std::string &lastName);
};

#endif // BACKEND_USER_H

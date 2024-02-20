#include "User.h"

User::User(int userID, int userType)
{
    this->userID = userID;
    this->userType = userType;
}

User::User(int userID, int userType, std::string username, std::string password, std::string email,
           std::string firstName, std::string lastName)
{
    this->userID = userID;
    this->userType = userType;
    this->username = username;
    this->password = password;
    this->email = email;
    this->firstName = firstName;
    this->lastName = lastName;
}

int User::getUserID() const
{
    return userID;
}

void User::setUserID(int userID)
{
    User::userID = userID;
}

int User::getUserType() const
{
    return userType;
}

void User::setUserType(int userType)
{
    User::userType = userType;
}

std::string User::getUsername() const
{
    return username;
}

void User::setUsername(const std::string &username)
{
    User::username = username;
}

std::string User::getPassword() const
{
    return password;
}

void User::setPassword(const std::string &password)
{
    User::password = password;
}

std::string User::getEmail() const
{
    return email;
}

void User::setEmail(const std::string &email)
{
    User::email = email;
}

std::string User::getFirstName() const
{
    return firstName;
}

void User::setFirstName(const std::string &firstName)
{
    User::firstName = firstName;
}

std::string User::getLastName() const
{
    return lastName;
}

void User::setLastName(const std::string &lastName)
{
    User::lastName = lastName;
}
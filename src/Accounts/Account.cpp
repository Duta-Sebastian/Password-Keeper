#include "Account.h"

Account::Account(const std::string &username, const std::string &password) :
    username(username), password(password) {}

std::string Account::getUsername() const {
    return this->username;
}

std::string Account::getPassword() const {
    return this->password;
}

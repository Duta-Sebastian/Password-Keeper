#include "User.h"
#include <iostream>
#include <utility>

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "username: " << user.username << '\n' << "password: " << user.passwordHash << '\n';
    return os;
}

User::User(std::string username, const std::string &password)
    : username(std::move(username)), passwordHash(password), userId(-1) {}

User::User(std::string username, PasswordHash passwordHash)
    : username(std::move(username)), passwordHash(std::move(passwordHash)), userId(-1) {
}

User::User(const User & otherUser): passwordHash(otherUser.passwordHash) {
    this->username = otherUser.username;
    this->userId = otherUser.userId;
}


std::string User::getUsername() const {
    return this->username;
}

std::string User::getPasswordHash() const {
    return this->passwordHash.getPasswordHash();
}

std::string User::getPasswordSalt() const {
    return this->passwordHash.getPasswordSalt();
}

int User::getUserId() const {
    return this->userId;
}

void User::setUserId(const int id) {
    this->userId = id;
}


//
// Created by sebid on 10/26/2024.
//

#include "User.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "username: " << user.username << '\n' << "password: " << user.password << '\n';
    return os;
}

User::User(const std::string &username, const std::string &password): username(username) {
    this->password = password;
}

#include "Account.h"

#include <iostream>
#include <utility>

Account::Account(std::string username, std::string password) :
    username(std::move(username)), password(std::move(password)) {}

std::string Account::getUsername() const {
    return this->username;
}

std::string Account::getPassword() const {
    return this->password;
}

void Account::show() const {
    std::cout << "---------------------------------\n";
    std::cout << "Account details:\n";
    showAccountDetails();
    std::cout << "\n";
}
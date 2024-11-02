#include "Auth.h"

#include <iostream>
#include <utility>

Auth::Auth(std::string username, std::string password)
    : username(std::move(username)), password(std::move(password)) {
}

User Auth::createAccount() const {
    try {
        auto currentUser = User(username, password);
        database.createAccount(currentUser);
        currentUser.setUserId(database.getCurrentUserId(currentUser.getUsername()));
        return currentUser;
    } catch (std::exception&) {
        throw;
    }
}

User Auth::login() const {
    try {
        auto [storedPasswordSalt, storedPasswordHash] = database.getLoginInformation(username);
        if (const auto hashedInputPassword = PasswordHash(password, storedPasswordSalt);
            hashedInputPassword.getPasswordHash() == storedPasswordHash) {
            auto currentUser = User(username, hashedInputPassword);
            currentUser.setUserId(database.getCurrentUserId(currentUser.getUsername()));
            std::cout << "login successful";
            return currentUser;
        }
        throw std::invalid_argument("Wrong password");
    } catch (std::exception&) {
        throw;
    }
}

std::ostream& operator<<(std::ostream& os, const Auth& auth) {
    os<< "Auth: " << auth.username << " " << auth.password<<std::endl;
    return os;
}


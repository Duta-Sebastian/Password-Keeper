#ifndef AUTH_H
#define AUTH_H
#include "Database.h"
#include "../User/User.h"

class Auth {
    Database &database = Database::getDatabaseInstance();
    std::string username;
    std::string password;

public:
    explicit Auth(std::string, std::string);

    [[nodiscard]] User createAccount() const;

    [[nodiscard]] User login() const;

    friend std::ostream &operator<<(std::ostream &os, const Auth &auth);
};


#endif //AUTH_H

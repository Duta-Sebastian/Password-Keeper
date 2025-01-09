#ifndef AUTH_H
#define AUTH_H
#include "Database.h"
#include "../User/User.h"

class Auth {
    std::unique_ptr<Database> database;
    std::string username;
    std::string password;

public:
    explicit Auth(std::string, std::string);

    ~Auth();

    [[nodiscard]] User createAccount() const;

    [[nodiscard]] User login() const;
};


#endif //AUTH_H

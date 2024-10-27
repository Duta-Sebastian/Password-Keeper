#ifndef AUTH_H
#define AUTH_H
#include "Database.h"
#include "../User/User.h"

class Auth {
    Database &database = Database::getDatabaseInstance();
    std::string username;
    std::string password;
public:
    explicit Auth(std::string , std::string );

    [[nodiscard]] User createAccount() const;
    User login() const;
};



#endif //AUTH_H

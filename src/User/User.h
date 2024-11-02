#ifndef USER_H
#define USER_H
#include <string>

#include "../Utils/PasswordHash.h"


class User {
    std::string username;
    PasswordHash passwordHash;
    int userId;
public:
    User(std::string, const std::string&);
    User(std::string, PasswordHash);
    User(const User&);
    User& operator=(const User&);
    friend std::ostream& operator<<(std::ostream& os, const User& user);
    [[nodiscard]] std::string getUsername() const;
    [[nodiscard]] std::string getPasswordHash() const;
    [[nodiscard]] std::string getPasswordSalt() const;
    [[nodiscard]] int getUserId() const;
    void setUserId(int);
};


#endif //USER_H

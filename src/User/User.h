#ifndef USER_H
#define USER_H
#include <string>

#include "../Utils/PasswordHash.h"


class User {
    std::string username;
    PasswordHash passwordHash;
    int userId;
    static int currentUserId;
public:
    User(std::string, const std::string&);
    User(std::string, PasswordHash);
    User(int, std::string, const std::string &, std::string);
    bool operator==(const User &) const;
    friend std::ostream& operator<<(std::ostream& os, const User& user);
    [[nodiscard]] std::string getUsername() const;
    [[nodiscard]] std::string getPasswordHash() const;
    [[nodiscard]] std::string getPasswordSalt() const;
    [[nodiscard]] int getUserId() const;
    void setUserId(int);

    static void setCurrentUserId(int);
    static int getCurrentUserId();
};


#endif //USER_H

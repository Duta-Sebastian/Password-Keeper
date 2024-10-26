//
// Created by sebid on 10/26/2024.
//

#ifndef USER_H
#define USER_H
#include <string>


class User {
    std::string username;
    std::string password;
public:
    User(const std::string& username, const std::string& password);
    friend std::ostream& operator<<(std::ostream& os, const User& user);

};


#endif //USER_H

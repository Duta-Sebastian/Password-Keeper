#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include "../Utils/AccountType.cpp"

class Account {
protected:
    std::string username;
    std::string password;
    [[nodiscard]] virtual AccountType getAccountType() const = 0;
    virtual void showAccountDetails() const = 0;
public:
    Account(std::string, std::string);
    virtual void addAccount() = 0;
    virtual ~Account() = default;
    void show() const;
    [[nodiscard]] virtual std::string getUsername() const;
    [[nodiscard]] virtual std::string getPassword() const;
};



#endif //ACCOUNT_H

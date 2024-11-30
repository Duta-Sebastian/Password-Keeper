#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>

enum AccountType {
    BankAccountType,
    EmailAccountType,
    SocialMediaAccountType
};

class Account {
protected:
    std::string username;
    std::string password;
    [[nodiscard]] virtual AccountType getAccountType() const = 0;
public:
    Account(std::string, std::string);
    virtual void addAccount() = 0;
    virtual ~Account() = default;

    [[nodiscard]] virtual std::string getUsername() const;
    [[nodiscard]] virtual std::string getPassword() const;
};



#endif //ACCOUNT_H

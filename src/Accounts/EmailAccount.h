#ifndef EMAILACCOUNT_H
#define EMAILACCOUNT_H
#include "Account.h"


class EmailAccount final: public Account {
    std::string emailAddress;
    std::string mailProvider;
    [[nodiscard]] AccountType getAccountType() const override;
public:
    explicit EmailAccount(std::string, std::string, std::string, std::string);

    void addAccount() override;

    [[nodiscard]] std::string getEmailAddress() const;
    [[nodiscard]] std::string getMailProvider() const;
};



#endif //EMAILACCOUNT_H

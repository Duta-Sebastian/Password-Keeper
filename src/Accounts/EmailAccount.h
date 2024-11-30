#ifndef EMAILACCOUNT_H
#define EMAILACCOUNT_H
#include "Account.h"


class EmailAccount final: public Account {
    std::string emailAddress;
    std::string mailProvider;
    [[nodiscard]] AccountType getAccountType() const override;
public:
    explicit EmailAccount(const std::string&, const std::string&, const std::string&, const std::string&);

    void addAccount() override;

    [[nodiscard]] std::string getEmailAddress() const;
    [[nodiscard]] std::string getMailProvider() const;
};



#endif //EMAILACCOUNT_H

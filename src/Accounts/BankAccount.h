#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include "Account.h"


class BankAccount final : public Account {
    std::string IBAN;
    std::string bank;
    [[nodiscard]] AccountType getAccountType() const override;
public:
    BankAccount(const std::string &, const std::string &, std::string , std::string );
    void addAccount() override;

    [[nodiscard]] std::string getIBAN() const;
    [[nodiscard]] std::string getBank() const;
};



#endif //BANKACCOUNT_H

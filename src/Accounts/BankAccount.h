#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <Account.h>
#include <AccountType.h>

class BankAccount final : public Account {
    std::string IBAN;
    std::string bank;

    [[nodiscard]] AccountType getAccountType() const override;

    void showAccountDetails() const override;

public:
    BankAccount(std::string, std::string, std::string, std::string);

    void addAccount() override;

    [[nodiscard]] std::string getIBAN() const;

    [[nodiscard]] std::string getBank() const;

    bool operator==(const BankAccount &) const;
};


#endif //BANKACCOUNT_H

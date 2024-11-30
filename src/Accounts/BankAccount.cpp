#include "BankAccount.h"

#include <Database.h>

BankAccount::BankAccount(std::string username, std::string password,
                         std::string IBAN, std::string bank)
    : Account(std::move(username),std::move(password)), IBAN(std::move(IBAN)), bank(std::move(bank)){}

AccountType BankAccount::getAccountType() const {
    return BankAccountType;
}

void BankAccount::addAccount() {
    const Database &database = Database::getDatabaseInstance();
    const auto bankAccount = std::make_shared<BankAccount>(*this);
    database.addUserDefinedAccount(bankAccount, this->getAccountType());
}

std::string BankAccount::getIBAN() const {
    return this->IBAN;
}

std::string BankAccount::getBank() const {
    return this->bank;
}

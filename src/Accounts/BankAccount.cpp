#include "BankAccount.h"

#include <Database.h>
#include <iostream>

BankAccount::BankAccount(std::string username, std::string password,
                         std::string IBAN, std::string bank)
    : Account(std::move(username),std::move(password)), IBAN(std::move(IBAN)), bank(std::move(bank)){}

AccountType BankAccount::getAccountType() const {
    return AccountType::BankAccountType;
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

void BankAccount::showAccountDetails() const {
    std::cout << "Account Type: " << getAccountTypeString(this->getAccountType())<< "\n"
              << "Username: " << this->username << "\n"
              << "Password: " << this->password << "\n"
              << "Email Address: " << this->IBAN << "\n"
              << "Mail Provider: " << this->bank;
}
#include <AccountType.h>
#include <BankAccount.h>

#include <Database.h>
#include <iostream>

BankAccount::BankAccount(std::string username, std::string password,
                         std::string IBAN, std::string bank)
    : Account(std::move(username), std::move(password)), IBAN(std::move(IBAN)), bank(std::move(bank)) {
}

AccountType BankAccount::getAccountType() const {
    return AccountType::BankAccountType;
}

void BankAccount::addAccount() {
    auto database = DatabasePool::getInstance().acquire();
    const auto bankAccount = std::make_shared<BankAccount>(*this);
    database->addUserDefinedAccount(bankAccount, this->getAccountType());
    database.release();
}

std::string BankAccount::getIBAN() const {
    return this->IBAN;
}

std::string BankAccount::getBank() const {
    return this->bank;
}

bool BankAccount::operator==(const BankAccount &rhs) const {
    return this->username == rhs.username && this->password == rhs.password
           && this->IBAN == rhs.IBAN && this->bank == rhs.bank;
}

void BankAccount::showAccountDetails() const {
    std::cout << "Account Type: " << getAccountTypeString(this->getAccountType()) << "\n"
            << "Username: " << this->username << "\n"
            << "Password: " << this->password << "\n"
            << "IBAN: " << this->IBAN << "\n"
            << "Bank: " << this->bank;
}

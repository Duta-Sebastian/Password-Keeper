#include <AccountType.h>
#include <EmailAccount.h>

#include <Database.h>
#include <iostream>

AccountType EmailAccount::getAccountType() const {
    return AccountType::EmailAccountType;
}

EmailAccount::EmailAccount(std::string username, std::string password,
                           std::string emailAddress, std::string mailProvider)
    : Account(std::move(username), std::move(password)),
      emailAddress(std::move(emailAddress)), mailProvider(std::move(mailProvider)) {
}

void EmailAccount::addAccount() {
    auto database = DatabasePool::getInstance().acquire();
    const auto emailAccount = std::make_shared<EmailAccount>(*this);
    database->addUserDefinedAccount(emailAccount, this->getAccountType());
    database.release();
}

std::string EmailAccount::getEmailAddress() const {
    return this->emailAddress;
}

std::string EmailAccount::getMailProvider() const {
    return this->mailProvider;
}

bool EmailAccount::operator==(const EmailAccount &rhs) const {
    return this->username == rhs.username && this->password == rhs.password &&
        this->emailAddress == rhs.emailAddress && this->mailProvider == rhs.mailProvider;
}

void EmailAccount::showAccountDetails() const {
    std::cout << "Account Type: " << getAccountTypeString(this->getAccountType()) << "\n"
            << "Username: " << this->username << "\n"
            << "Password: " << this->password << "\n"
            << "Email Address: " << this->emailAddress << "\n"
            << "Mail Provider: " << this->mailProvider;
}

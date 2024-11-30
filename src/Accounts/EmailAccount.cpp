#include "EmailAccount.h"

#include <Database.h>

AccountType EmailAccount::getAccountType() const {
    return EmailAccountType;
}

EmailAccount::EmailAccount(const std::string &username, const std::string &password,
                           const std::string &emailAddress, const std::string &mailProvider)
    : Account(username, password), emailAddress(emailAddress), mailProvider(mailProvider) {}

void EmailAccount::addAccount() {
    const Database &database = Database::getDatabaseInstance();
    const auto emailAccount = std::make_shared<EmailAccount>(*this);
    database.addUserDefinedAccount(emailAccount, this->getAccountType());
}

std::string EmailAccount::getEmailAddress() const {
    return this->emailAddress;
}

std::string EmailAccount::getMailProvider() const {
    return this->mailProvider;
}
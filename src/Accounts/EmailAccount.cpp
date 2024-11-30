#include "EmailAccount.h"

#include <Database.h>

AccountType EmailAccount::getAccountType() const {
    return EmailAccountType;
}

EmailAccount::EmailAccount(std::string username, std::string password,
                           std::string emailAddress, std::string mailProvider)
    : Account(std::move(username), std::move(password)),
      emailAddress(std::move(emailAddress)), mailProvider(std::move(mailProvider)) {}

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
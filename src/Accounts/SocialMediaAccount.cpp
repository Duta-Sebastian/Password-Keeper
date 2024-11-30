#include "SocialMediaAccount.h"

#include <Database.h>

AccountType SocialMediaAccount::getAccountType() const {
    return SocialMediaAccountType;
}

SocialMediaAccount::SocialMediaAccount(std::string username, std::string password,
                                       std::string platform, std::string profileUrl)
    : Account(std::move(username), std::move(password)),
      platform(std::move(platform)), profileUrl(std::move(profileUrl)) {}

void SocialMediaAccount::addAccount() {
    const Database &database = Database::getDatabaseInstance();
    const auto emailAccount = std::make_shared<SocialMediaAccount>(*this);
    database.addUserDefinedAccount(emailAccount, this->getAccountType());
}

std::string SocialMediaAccount::getPlatform() const {
    return this->platform;
}

std::string SocialMediaAccount::getProfileUrl() const {
    return this->profileUrl;
}
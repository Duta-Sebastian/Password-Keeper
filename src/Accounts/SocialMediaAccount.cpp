#include "SocialMediaAccount.h"

#include <Database.h>

AccountType SocialMediaAccount::getAccountType() const {
    return SocialMediaAccountType;
}

SocialMediaAccount::SocialMediaAccount(const std::string &username, const std::string& password,
                                       const std::string &platform, const std::string & profileUrl)
    : Account(username, password), platform(platform), profileUrl(profileUrl) {}

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
#include <AccountType.h>
#include <SocialMediaAccount.h>

#include <Database.h>
#include <iostream>

AccountType SocialMediaAccount::getAccountType() const {
    return AccountType::SocialMediaAccountType;
}

SocialMediaAccount::SocialMediaAccount(std::string username, std::string password,
                                       std::string platform, std::string profileUrl)
    : Account(std::move(username), std::move(password)),
      platform(std::move(platform)), profileUrl(std::move(profileUrl)) {
}

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

bool SocialMediaAccount::operator==(const SocialMediaAccount &rhs) const {
    return this->username == rhs.username && this->password == rhs.password &&
        this->platform == rhs.platform && this->profileUrl == rhs.profileUrl;
}

void SocialMediaAccount::showAccountDetails() const {
    std::cout << "Account Type: " << getAccountTypeString(this->getAccountType()) << "\n"
            << "Username: " << this->username << "\n"
            << "Password: " << this->password << "\n"
            << "Platform: " << this->platform << "\n"
            << "Profile URL: " << this->profileUrl;
}

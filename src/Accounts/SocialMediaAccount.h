#ifndef SOCIALMEDIAACCOUNT_H
#define SOCIALMEDIAACCOUNT_H
#include <Account.h>
#include <AccountType.h>
class SocialMediaAccount final : public Account {
    std::string platform;
    std::string profileUrl;

    [[nodiscard]] AccountType getAccountType() const override;

    void showAccountDetails() const override;

public:
    SocialMediaAccount(std::string, std::string, std::string, std::string);

    void addAccount() override;

    [[nodiscard]] std::string getPlatform() const;

    [[nodiscard]] std::string getProfileUrl() const;

    bool operator==(const SocialMediaAccount&) const;
};


#endif //SOCIALMEDIAACCOUNT_H

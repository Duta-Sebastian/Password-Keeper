#ifndef SOCIALMEDIAACCOUNT_H
#define SOCIALMEDIAACCOUNT_H
#include "Account.h"


class SocialMediaAccount final : public Account {
    std::string platform;
    std::string profileUrl;
    [[nodiscard]] AccountType getAccountType() const override;
public:
    SocialMediaAccount(std::string, std::string, std::string, std::string);

    void addAccount() override;

    [[nodiscard]] std::string getPlatform() const;
    [[nodiscard]] std::string getProfileUrl() const;
};



#endif //SOCIALMEDIAACCOUNT_H

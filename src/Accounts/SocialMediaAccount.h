#ifndef SOCIALMEDIAACCOUNT_H
#define SOCIALMEDIAACCOUNT_H
#include "Account.h"


class SocialMediaAccount final : public Account {
    std::string platform;
    std::string profileUrl;
    [[nodiscard]] AccountType getAccountType() const override;
public:
    SocialMediaAccount(const std::string&, const std::string&, const std::string&, const std::string&);

    void addAccount() override;

    [[nodiscard]] std::string getPlatform() const;
    [[nodiscard]] std::string getProfileUrl() const;
};



#endif //SOCIALMEDIAACCOUNT_H

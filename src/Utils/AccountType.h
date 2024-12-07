#ifndef ACCOUNTTYPE_H
#define ACCOUNTTYPE_H

#include <string_view>

enum class AccountType {
    BankAccountType,
    EmailAccountType,
    SocialMediaAccountType
};

constexpr std::string_view getAccountTypeString(const AccountType& accountType) {
    switch (accountType) {
        case AccountType::BankAccountType:
            return "Bank Account";
        case AccountType::EmailAccountType:
            return "Email Account";
        case AccountType::SocialMediaAccountType:
            return "Social Media Account";
        default:
            return "Unknown Account Type";
    }
}

#endif //ACCOUNTTYPE_H

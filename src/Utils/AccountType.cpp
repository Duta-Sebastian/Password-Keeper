#include <string>

enum class AccountType {
    BankAccountType,
    EmailAccountType,
    SocialMediaAccountType
};

constexpr std::string getAccountTypeString(const AccountType &accountType) {
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

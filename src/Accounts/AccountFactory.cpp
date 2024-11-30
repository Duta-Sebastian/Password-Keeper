#include "AccountFactory.h"

#include <BankAccount.h>
#include <EmailAccount.h>
#include <SocialMediaAccount.h>

std::shared_ptr<Account> AccountFactory::accountFactory(const AccountType accountType,
                                                        std::map<std::string, std::string> accountDetails) {
    switch (accountType) {
        case AccountType::BankAccountType : {
            return std::make_shared<BankAccount>(accountDetails["username"], accountDetails["password"],
                                                 accountDetails["IBAN"], accountDetails["bank"]);
        }
        case AccountType::EmailAccountType : {
            return std::make_shared<EmailAccount>(accountDetails["username"], accountDetails["password"],
                                                  accountDetails["emailAddress"], accountDetails["mailProvider"]);
        }
        case AccountType::SocialMediaAccountType : {
            return std::make_shared<SocialMediaAccount>(accountDetails["username"], accountDetails["password"],
                                                        accountDetails["platform"], accountDetails["profileUrl"]);
        }
        default: {
            throw std::invalid_argument("Invalid accountType");
        }
    }
}

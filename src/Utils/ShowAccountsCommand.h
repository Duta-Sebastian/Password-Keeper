#ifndef SHOWACCOUNTSCOMMAND_H
#define SHOWACCOUNTSCOMMAND_H

#include <AccountType.h>
#include <Database.h>
#include <iostream>
namespace ShowAccountsCommands {
    template<AccountType T>
    void showAccountsCommand() {
        for (const auto &database = Database::getDatabaseInstance();
             const auto &account: database.getAccountsByType(T)) {
            account->show();
             }
        std::cout << "---------------------------------\n";
    } ;

    inline void showAllAccounts() {
        showAccountsCommand<AccountType::BankAccountType>();
        showAccountsCommand<AccountType::EmailAccountType>();
        showAccountsCommand<AccountType::SocialMediaAccountType>();
    }
}

#endif //SHOWACCOUNTSCOMMAND_H

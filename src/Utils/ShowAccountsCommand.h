#ifndef SHOWACCOUNTSCOMMAND_H
#define SHOWACCOUNTSCOMMAND_H

#include <AccountType.h>
#include <Database.h>
#include <iostream>
namespace ShowAccountsCommands {
    template<AccountType T>
    void showAccountsCommand() {
        auto database = DatabasePool::getInstance().acquire();
        for (const auto &account: database->getAccountsByType(T)) {
            account->show();
             }
        std::cout << "---------------------------------\n";
        DatabasePool::getInstance().release(database);
    } ;

    inline void showAllAccounts() {
        showAccountsCommand<AccountType::BankAccountType>();
        showAccountsCommand<AccountType::EmailAccountType>();
        showAccountsCommand<AccountType::SocialMediaAccountType>();
    }
}

#endif //SHOWACCOUNTSCOMMAND_H

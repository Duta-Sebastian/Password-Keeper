#include <Database.h>

namespace ShowAccountsCommands {

    template <AccountType T>
    void showAccountsCommand() {
        for (const auto &database = Database::getDatabaseInstance();
             const auto &account : database.getAccountsByType(T)) {
            account->show();
        }
    }

    void showAllAccounts() {
        showAccountsCommand<AccountType::BankAccountType>();
        showAccountsCommand<AccountType::EmailAccountType>();
        showAccountsCommand<AccountType::SocialMediaAccountType>();
    }
}
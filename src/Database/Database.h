#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>

#include <Account.h>
#include <User.h>
#include "DatabasePool.h"

class Database {
    std::shared_ptr<pqxx::connection> connection;
    static std::string connString;
public:
    Database();

    ~Database();

    [[nodiscard]] std::tuple<std::string, std::string> getLoginInformation(const std::string &) const;

    static void setConnString(const std::string &);

    void createAccount(const User& currentUser) const;

    [[nodiscard]] int getCurrentUserId(const std::string&) const;

    [[nodiscard]] int getNumberOfUsers() const;

    User getUserByUsername(std::string &username) const;

    void addUserDefinedAccount(const std::shared_ptr<Account> &account, const AccountType &) const;

    std::vector<std::shared_ptr<Account>> getAccountsByType(const AccountType &accountType) const;

    std::vector<std::shared_ptr<Account>> getAllAccounts() const;
};


#endif //DATABASE_H
#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>

#include <Account.h>
#include <User.h>

class Database {
    std::unique_ptr<pqxx::connection> connection;
    static std::string connString;

    Database();

    ~Database();

public:
    Database(const Database &) = delete;

    Database &operator=(const Database &) = delete;

    Database(Database &&) = delete;

    Database &operator=(Database &&) = delete;

    [[nodiscard]] std::tuple<std::string, std::string> getLoginInformation(const std::string &) const;

    static Database &getDatabaseInstance();

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
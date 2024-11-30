#include "Database.h"

#include <iostream>

#include "../Accounts/BankAccount.h"
#include "../Accounts/EmailAccount.h"
#include "../Accounts/SocialMediaAccount.h"

std::string Database::connString;

Database::Database() {
    try {
        connection = std::make_unique<pqxx::connection>(connString);
        if (!connection->is_open()) {
            throw std::runtime_error("Database exists but a connection couldn't be established");
        }
    } catch (const std::exception &) {
        connection = nullptr;
        throw ;
    }
}

Database::~Database() {
    if (connection) {
        connection->close();
    }
    connection = nullptr;
}

Database &Database::getDatabaseInstance() {
    static Database databaseInstance;
    return databaseInstance;
}

void Database::setConnString(const std::string &connectionString) {
    connString = connectionString;
}

void Database::createAccount(const User &currentUser) const {
    pqxx::work work(*connection);
    try {
        work.exec_params("INSERT INTO users (username, passwordSalt, passwordHash)"
                         " VALUES ($1, $2, $3)",
                         currentUser.getUsername(),
                         currentUser.getPasswordSalt(),
                         currentUser.getPasswordHash()
        );
        work.commit();
    }
    catch (const pqxx::unique_violation& e) {
        std::cerr << e.what() << std::endl;
        throw;
    }
    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        throw;
    }
}

std::tuple<std::string, std::string> Database::getLoginInformation(const std::string &username) const {
    pqxx::work work(*connection);
    try {
        const auto queryResult = work.exec_params("SELECT passwordSalt, passwordHash"
                                                  " FROM users WHERE username = $1", username);
        if (queryResult.empty()) {
            throw std::runtime_error("User not found");
        }
        auto passwordSalt = queryResult[0][0].as<std::string>();
        auto passwordHash = queryResult[0][1].as<std::string>();
        return {passwordSalt, passwordHash};
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        throw;
    }
}

int Database::getCurrentUserId(const std::string &username) const {
    pqxx::work work(*connection);
    try {
        const auto queryResult = work.exec_params("SELECT id FROM users WHERE username = $1",
                                                  username);
        if (queryResult.empty())
            throw std::runtime_error("User not found");
        return queryResult[0][0].as<int>();
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        throw;
    }
}

int Database::getNumberOfUsers() const {
    pqxx::work work(*connection);
    try {
        const auto queryResult = work.exec_params("SELECT COUNT(*) FROM users");
        return queryResult[0][0].as<int>();
    }
    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        throw;
    }
}

User Database::getUserByUsername(std::string &username) const {
    pqxx::work work(*connection);
    try {
        const auto queryResult = work.exec_params("SELECT id, username, passwordSalt, passwordHash FROM users"
                                                  " WHERE username = $1", username);
        const int _userId = queryResult[0][0].as<int>();
        const auto _username = queryResult[0][1].as<std::string>();
        const auto _passwordSalt = queryResult[0][2].as<std::string>();
        const auto _passwordHash = queryResult[0][3].as<std::string>();
        return {_userId, _username, _passwordHash,
            _passwordSalt};
    }
    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        throw;
    }
}

void Database::addUserDefinedAccount(const std::shared_ptr<Account>& account,const AccountType &accountType) const {
    pqxx::work work(*connection);
    std::string query;
    switch (accountType) {
        case BankAccountType: {
            const auto bankAccount = dynamic_pointer_cast<BankAccount>(account);
            query = "INSERT INTO bankaccounts VALUES (" +
                work.quote(User::getCurrentUserId()) + ", " +
                work.quote(bankAccount->getUsername()) + ", " +
                work.quote(bankAccount->getPassword()) + ", " +
                work.quote(bankAccount->getIBAN()) + ", " +
                work.quote(bankAccount->getBank()) + ");";
            break;
        }
        case EmailAccountType: {
            const auto emailAccount = dynamic_pointer_cast<EmailAccount>(account);
            query = "INSERT INTO bankaccounts VALUES (" +
                work.quote(User::getCurrentUserId()) + ", " +
                work.quote(emailAccount->getUsername()) + ", " +
                work.quote(emailAccount->getPassword()) + ", " +
                work.quote(emailAccount->getEmailAddress()) + ", " +
                work.quote(emailAccount->getMailProvider()) + ");";
            break;
        }
        case SocialMediaAccountType: {
            const auto socialMediaAccount = dynamic_pointer_cast<SocialMediaAccount>(account);
            query = "INSERT INTO bankaccounts VALUES (" +
                work.quote(User::getCurrentUserId()) + ", " +
                work.quote(socialMediaAccount->getUsername()) + ", " +
                work.quote(socialMediaAccount->getPassword()) + ", " +
                work.quote(socialMediaAccount->getPlatform()) + ", " +
                work.quote(socialMediaAccount->getProfileUrl()) + ");";
            break;
        }
        default: {
            work.abort();
            throw std::runtime_error("Unknown account type");
        }
    }
    try {
        work.exec_params(query);
        work.commit();
    }
    catch (const pqxx::data_exception &e) {
        throw std::runtime_error("Data error");
    }

}

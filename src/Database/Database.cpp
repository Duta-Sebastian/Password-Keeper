#include <Database.h>
#include <iostream>

#include <AccountExceptions.h>
#include <AccountFactory.h>
#include <AccountType.h>
#include <BankAccount.h>
#include <DatabaseExceptions.h>
#include <EmailAccount.h>
#include <SocialMediaAccount.h>
#include <VectorUtils.h>

std::string Database::connString;

Database::Database() {
    try {
        connection = std::make_shared<pqxx::connection>(connString);
        if (!connection->is_open()) {
            throw FailedToOpen("Database exists but a connection couldn't be established");
        }
    } catch (const FailedToOpen& ) {
        connection = nullptr;
        throw;
    }
}

Database::~Database() {
    if (connection) {
        connection->close();
    }
    connection = nullptr;
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
    } catch (const pqxx::unique_violation &e) {
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
    } catch (const std::exception &e) {
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
        return {
            _userId, _username, _passwordHash,
            _passwordSalt
        };
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        throw;
    }
}

void Database::addUserDefinedAccount(const std::shared_ptr<Account> &account, const AccountType &accountType) const {
    pqxx::work work(*connection);
    std::string query;
    switch (accountType) {
        case AccountType::BankAccountType: {
            const auto bankAccount = dynamic_pointer_cast<BankAccount>(account);
            query = "INSERT INTO bankaccounts VALUES (" +
                    work.quote(User::getCurrentUserId()) + ", " +
                    work.quote(bankAccount->getUsername()) + ", " +
                    work.quote(bankAccount->getPassword()) + ", " +
                    work.quote(bankAccount->getIBAN()) + ", " +
                    work.quote(bankAccount->getBank()) + ");";
            break;
        }
        case AccountType::EmailAccountType: {
            const auto emailAccount = dynamic_pointer_cast<EmailAccount>(account);
            query = "INSERT INTO emailaccounts VALUES (" +
                    work.quote(User::getCurrentUserId()) + ", " +
                    work.quote(emailAccount->getUsername()) + ", " +
                    work.quote(emailAccount->getPassword()) + ", " +
                    work.quote(emailAccount->getEmailAddress()) + ", " +
                    work.quote(emailAccount->getMailProvider()) + ");";
            break;
        }
        case AccountType::SocialMediaAccountType: {
            const auto socialMediaAccount = dynamic_pointer_cast<SocialMediaAccount>(account);
            query = "INSERT INTO socialmediaaccounts VALUES (" +
                    work.quote(User::getCurrentUserId()) + ", " +
                    work.quote(socialMediaAccount->getUsername()) + ", " +
                    work.quote(socialMediaAccount->getPassword()) + ", " +
                    work.quote(socialMediaAccount->getPlatform()) + ", " +
                    work.quote(socialMediaAccount->getProfileUrl()) + ");";
            break;
        }
        default: {
            work.abort();
            throw AccountTypeExceptions("The addUserDefinedAccount method failed!");
        }
    }
    try {
        work.exec_params(query);
        work.commit();
    } catch ([[maybe_unused]] const pqxx::data_exception &e) {
        throw FailedToCommit("The addUserDefinedAccount method failed!");
    }
}

/// TODO Maybe lambda functions?
std::vector<std::shared_ptr<Account> > Database::getAccountsByType(const AccountType &accountType) const {
    pqxx::work work(*connection);
    std::vector<std::shared_ptr<Account> > accounts;
    switch (accountType) {
        case AccountType::BankAccountType: {
            const auto queryResult = work.exec_params("Select * from bankaccounts where id=$1",
                                                      User::getCurrentUserId());
            for (const auto &row: queryResult) {
                accounts.push_back(AccountFactory::accountFactory(AccountType::BankAccountType, {
                                                                      {"username", row[1].as<std::string>()},
                                                                      {"password", row[2].as<std::string>()},
                                                                      {"IBAN", row[3].as<std::string>()},
                                                                      {"bank", row[4].as<std::string>()}
                                                                  }));
            }
            break;
        }
        case AccountType::EmailAccountType: {
            const auto queryResult = work.exec_params("Select * from emailaccounts where id=$1",
                                                      User::getCurrentUserId());
            for (const auto &row: queryResult) {
                accounts.push_back(AccountFactory::accountFactory(AccountType::EmailAccountType, {
                                                                      {"username", row[1].as<std::string>()},
                                                                      {"password", row[2].as<std::string>()},
                                                                      {"emailAddress", row[3].as<std::string>()},
                                                                      {"mailProvider", row[4].as<std::string>()}
                                                                  }));
            }
            break;
        }
        case AccountType::SocialMediaAccountType: {
            const auto queryResult = work.exec_params("Select * from socialmediaaccounts where id=$1",
                                                      User::getCurrentUserId());
            for (const auto &row: queryResult) {
                accounts.push_back(AccountFactory::accountFactory(AccountType::SocialMediaAccountType, {
                                                                      {"username", row[1].as<std::string>()},
                                                                      {"password", row[2].as<std::string>()},
                                                                      {"platform", row[3].as<std::string>()},
                                                                      {"profileUrl", row[4].as<std::string>()}
                                                                  }));
            }
            break;
        }
        default: {
            work.abort();
            throw AccountTypeExceptions("The getAccountsByType method failed!");
        }
    }
    return accounts;
}

std::vector<std::shared_ptr<Account> > Database::getAllAccounts() const {
    return getAccountsByType(AccountType::BankAccountType) +
           getAccountsByType(AccountType::EmailAccountType) +
           getAccountsByType(AccountType::SocialMediaAccountType);
}

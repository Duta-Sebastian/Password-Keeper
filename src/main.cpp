#include <DatabaseExceptions.h>
#include <iostream>

#include "AccountExceptions.h"
#include "AddAccountCommandTemplate.h"
#include "ShowAccountsCommand.cpp"
#include "Database/Database.h"

#include "Database/Auth.h"
#include "EnvironmentReader/EnvironmentReader.h"
#include "Logger/Logger.h"

void initializeDatabase() {
    auto &logger = Logger::getInstance();
    EnvironmentReader::getEnvReader();
    try {
        const std::string connString = EnvironmentReader::getConnString();
        Database::setConnString(connString);
        Database::getDatabaseInstance();
        logger.log(LogLevel::INFO, "Connected to database");
    }
    catch (EnvironmentVariableNotFound &e) {
        logger.log(LogLevel::LOG_ERROR, "Error initializing database connection: " + std::string(e.what()));
        throw ;
    }
    catch (FailedToOpen &e) {
        logger.log(LogLevel::LOG_ERROR, "Error initializing database connection: " + std::string(e.what()) + '\n');
        throw ;
    }
}

std::string promptCommand() {
    std::string command;
    while (true) {
        std::cout << "Please choose 'Login' or 'Create account': ";
        std::getline(std::cin, command);
        if (command == "Login" || command == "Create account") {
            std::flush(std::cout);
            break;
        }
        std::cout << "Invalid option. ";
        std::flush(std::cout);
    }
    return command;
}

std::tuple<std::string, std::string> promptUserInformation() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    return {username, password};
}

User handleUserAuth(const std::string &command, const std::tuple<std::string, std::string>& userInformation) {
    const Auth auth = std::apply([](auto&&... args) { return Auth(args...); }, userInformation);
    std::optional<User> currentUser;
    try {
        if(command == "Login") currentUser = auth.login();
        else currentUser = auth.createAccount() ;
    }
    catch (std::exception &e) {
        std::cout << e.what() << '\n';
        std::cout << "Invalid username or password.\n";
        throw;
    }
    return *currentUser;
}

void addAccountCommand() {
    auto &logger = Logger::getInstance();
    while (true) {
        std::cout<< "What type of account do you want to add? Choose the corresponding index!\n"
                 << "1. Bank Account\n" << "2. Email Account\n" << "3. Social Media Account\n" << "4. Exit\n";
        std::flush(std::cout);
        std::string command;
        std::cin >> command;
        int commandIndex;
        try {
            commandIndex = std::stoi(command);
        }
        catch ([[maybe_unused]] std::invalid_argument &e) {
            std::cout << "Invalid command!\n";
            continue;
        }
        try {
            switch (commandIndex) {
                case 1: {
                    AddAccountCommandTemplate<AccountType::BankAccountType>::addAccountCommand();
                    break;
                }
                case 2: {
                    AddAccountCommandTemplate<AccountType::EmailAccountType>::addAccountCommand();
                    break;
                }
                case 3: {
                    AddAccountCommandTemplate<AccountType::SocialMediaAccountType>::addAccountCommand();
                    break;
                }
                case 4: {
                    return ;
                }
                default:
                    std::cout << "Invalid command!\n";
            }
            logger.log(LogLevel::INFO, "Successfully added account!");
        }
        catch (FailedToCommit &e) {
            logger.log(LogLevel::LOG_ERROR,e.what());
            std::cout << e.what() << '\n';
        }
        catch (AccountTypeExceptions &e) {
            logger.log(LogLevel::LOG_ERROR,e.what());
            std::cout << e.what() << '\n';
        }
        catch (...) {
            logger.log(LogLevel::LOG_ERROR, "Unknown error encountered!");
            std::cout << "Unknown error encountered!\n";
        }
    }
}
void showAccountsCommand() {
    auto &logger = Logger::getInstance();
    while (true) {
        std::cout<< "What type of accounts do you want to show? Choose the corresponding index!\n"
         << "1. Bank Account\n" << "2. Email Account\n"
         << "3. Social Media Account\n" << "4. All accounts\n" << "5. Exit\n";
        std::flush(std::cout);
        std::string command;
        std::cin >> command;
        int commandIndex;
        try {
            commandIndex = std::stoi(command);
        }
        catch ([[maybe_unused]] std::invalid_argument &e) {
            std::cout << "Invalid command!\n";
            continue;
        }
        try {
            switch (commandIndex) {
                case 1: {
                    ShowAccountsCommands::showAccountsCommand<AccountType::BankAccountType>();
                    break;
                }
                case 2: {
                    ShowAccountsCommands::showAccountsCommand<AccountType::EmailAccountType>();
                    break;
                }
                case 3: {
                    ShowAccountsCommands::showAccountsCommand<AccountType::SocialMediaAccountType>();
                    break;
                }
                case 4: {
                    ShowAccountsCommands::showAllAccounts();
                    break;
                }
                case 5: {
                    return ;
                }
                default:
                    std::cout << "Invalid command!\n";
            }
            logger.log(LogLevel::INFO, "Accounts showed successfully!");
        }
        catch (AccountTypeExceptions &e) {
            logger.log(LogLevel::LOG_ERROR,e.what());
            std::cout << e.what() << '\n';
        }
        catch (...) {
            logger.log(LogLevel::LOG_ERROR, "Unknown error encountered!");
            std::cout << "Unknown error encountered!\n";
        }
    }
}

void userInteraction() {
    while (true) {
        std::cout<< "Choose an option by inputting its index!\n" << "1. Add a new account\n"
                 << "2. Show accounts\n" << "3. Exit\n";
        std::string command = {};
        std::cin >> command;
        int commandIndex;
        try {
            commandIndex = std::stoi(command);
        }
        catch ([[maybe_unused]] std::invalid_argument &e) {
            std::cout << "Invalid command!\n";
            continue;
        }
        switch (commandIndex) {
            case 1: {
                addAccountCommand();
                break;
            }
            case 2: {
                showAccountsCommand();
                break;
            }
            case 3: {
                return ;
            }
            default:
                std::cout << "Invalid command!\n";
        }
    }
}

int main() {
    Logger::create("Logs");
    auto &logger = Logger::getInstance();
    logger.log(LogLevel::INFO, "Application started");
    try {
        initializeDatabase();
    }
    catch (...) {
        logger.log(LogLevel::LOG_ERROR, "Critical error encountered, application exiting");
        return 1;
    }
    const std::string command = promptCommand();
    while (true) {
        try {
            auto currentUser = handleUserAuth(command, promptUserInformation());
            User::setCurrentUserId(currentUser.getUserId());
            break;
        }
        catch (...) {
        }
    }
    userInteraction();
    return 0;
}

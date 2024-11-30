#include <iostream>

#include "AccountFactory.h"
#include "Accounts/BankAccount.h"
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
    } catch (std::exception &e) {
        logger.log(LogLevel::LOG_ERROR, "Error initializing database connection: " + std::string(e.what()) + '\n');
        throw std::runtime_error("Error initializing database connection" + std::string(e.what()) + '\n');
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
    // std::vector<std::shared_ptr<Account>> accounts;
    // accounts.push_back(AccountFactory::accountFactory(BankAccountType, {{"username", "sebi1"},{"password","1234"},
    //                                                                  {"IBAN", "123412412"}, {"bank", "bt"}}));
    // accounts.push_back(AccountFactory::accountFactory(BankAccountType, {{"username", "sebi1"},{"password","12345"},
    //                                                              {"IBAN", "1234124112"}, {"bank", "bt1"}}));
    // accounts.push_back(AccountFactory::accountFactory(EmailAccountType, {{"username", "sebi"},{"password","1234"},
    //                                                              {"emailAddress", "sebi1"},{"mailProvider","12345"}}));
    // accounts.push_back(AccountFactory::accountFactory(SocialMediaAccountType, {{"username", "sebi1"},{"password","1234"},
    //                                                              {"platform", "123412412"}, {"profileUrl", "b123t"}}));
    // for (const auto &account : accounts) {
    //     account->addAccount();
    // }
    auto vector = Database::getDatabaseInstance().getAllAccounts();

    return 0;
}

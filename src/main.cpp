#include <iostream>
#include "Database/Database.h"

#include "Database/Auth.h"
#include "EnvironmentReader/EnvironmentReader.h"
#include "Logger/Logger.h"
#include "Utils/EnvVarManager.h"

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

std::tuple<std::string, std::string> promptUserDetails() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    return {username, password};
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
    auto [username, password] = promptUserDetails();
    const Auth auth(username, password);
    std::optional<User> currentUser;
    if(command == "Login") currentUser = auth.login();
    else currentUser = auth.createAccount();
    std::cout<<*currentUser;
    const User copiedUser = *currentUser;
    std::cout<<copiedUser;
    std::cout<<auth;
    const auto &database = Database::getDatabaseInstance();
    std::cout<<database;
    std::cout<<logger;
    constexpr EnvVarManager envVarManager;
    std::cout<<&envVarManager;
    return 0;
}

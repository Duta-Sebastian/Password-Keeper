#include <iostream>

#include "Database/Database.h"
#include <pqxx/pqxx>

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
        logger.log(LogLevel::ERROR, "Error initializing database connection: " + std::string(e.what()) + '\n');
        throw std::runtime_error("Error initializing database connection");
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
    try {
        initializeDatabase();
    }
    catch (...) {
        return 1;
    }
    // std::string command = promptCommand();
    // auto [username, password] = promptUserDetails();
    // const Auth auth(username, password);
    // auto currentUser = auth.createAccount(); // this
    // std::cout<<currentUser;
    // const Auth auth2(username, password);
    // const auto currentUser = auth2.login();
    // std::cout<<currentUser;
    return 0;
}

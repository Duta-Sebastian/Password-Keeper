#include <iostream>

#include "Database/Database.h"
#include <pqxx/pqxx>

#include "Database/Auth.h"
#include "EnvironmentReader/EnvironmentReader.h"
#include "User/User.h"

void initializeDatabase() {
    EnvironmentReader::getEnvReader();
    try {
        const std::string connString = EnvironmentReader::getConnString();
        Database::setConnString(connString);
    } catch (const std::exception &e) {
        std::cerr << "Error initializing database connection: " << e.what() << std::endl;
        throw;
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

std::tuple<std::string , std::string> promptUserDetails() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    return {username, password};
}

int main() {
    try {
        initializeDatabase();
    } catch (const std::exception&) {
        return -1;
    }
    std::string command = promptCommand();
    auto [username, password] = promptUserDetails();
    // const Auth auth(username, password);
    // auto currentUser = auth.createAccount(); // this works
    const Auth auth2(username, password);
    auto currentUser = auth2.login();
    return 0;
}

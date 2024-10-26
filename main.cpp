#include "Database/Database.h"
#include <pqxx/pqxx>
#include "EnvironmentReader/EnvironmentReader.h"
#include "User/User.h"

void initializeDatabase() {
    auto &envReader = EnvironmentReader::getEnvReader();
    try {
        const std::string connString = envReader.getConnString();
        Database::setConnString(connString);
    } catch (const std::exception &e) {
        std::cerr << "Error initializing database connection: " << e.what() << std::endl;
        throw;
    }
}
int main() {
    try {
        initializeDatabase();
    } catch (const std::exception&) {
        return -1;
    }
    try {
        const Database &db = Database::getInstance();
        db.getVersion();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    return 0;
}

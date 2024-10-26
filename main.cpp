#include "Database/Database.h"
#include <pqxx/pqxx>
#include "EnvironmentReader/EnvironmentReader.h"

int main() {
    auto &envReader = EnvironmentReader::getEnvReader();
    try {
        std::string connString = envReader.getConnString();
        Database::setConnString(connString);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    try {
        Database &db = Database::getInstance();
        db.getVersion();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
}

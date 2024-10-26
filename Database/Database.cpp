#include "Database.h"

#include <iostream>

std::string Database::connString;

Database::Database() {
    printf("Database constructor\n");
    try {
        connection = std::make_unique<pqxx::connection>(connString);
        if (!connection->is_open()) {
            throw std::runtime_error("Error opening database");
        }
    } catch (const std::exception &e) {
        std::cerr << "Connection error: " << e.what() << std::endl;
        connection = nullptr;
    }
}

Database::~Database() {
    if (connection) {
        connection->close();
    }
}

Database &Database::getInstance() {
    static Database instance;
    return instance;
}

void Database::setConnString(const std::string &connString) {
    Database::connString = connString;
}

#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <pqxx/pqxx>

class Database {
    std::unique_ptr<pqxx::connection> connection;
    static std::string connString;

    Database();

    ~Database();

public:
    Database(const Database &) = delete;

    Database &operator=(const Database &) = delete;

    static Database &getInstance();

    static void setConnString(const std::string &);

    void getVersion() const {
        pqxx::work w(*connection);
        const pqxx::row r = w.exec1("SELECT 1");
        w.commit();
        std::cout << r[0].as<int>() << std::endl;
    }
};


#endif //DATABASE_H

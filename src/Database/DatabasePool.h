#ifndef DATABASEPOOL_H
#define DATABASEPOOL_H

#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>
#include "Database.h"

class Database;

class DatabasePool {
    std::queue<std::unique_ptr<Database>> pool;
    static std::unique_ptr<DatabasePool> instance;
    static std::mutex poolMutex;

    explicit DatabasePool(std::size_t maxSize);

public:
    static DatabasePool& getInstance(size_t initialSize = 10);

    DatabasePool(const DatabasePool&) = delete;

    DatabasePool& operator=(const DatabasePool&) = delete;

    ~DatabasePool();

    std::unique_ptr<Database> acquire();

    void release(std::unique_ptr<Database> dbInstance);
};

#endif // DATABASEPOOL_H

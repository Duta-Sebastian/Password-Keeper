#include <memory>
#include "DatabasePool.h"

std::unique_ptr<DatabasePool> DatabasePool::instance = nullptr;
std::mutex DatabasePool::poolMutex;

DatabasePool::DatabasePool(std::size_t maxSize){
    for (std::size_t i = 0; i < maxSize; ++i) {
        pool.emplace(std::make_unique<Database>());
    }
}

DatabasePool::~DatabasePool() {
    std::lock_guard<std::mutex> lock(poolMutex);
    while (!pool.empty()) {
        pool.pop();
    }
}

std::unique_ptr<Database> DatabasePool::acquire() {
    std::unique_lock<std::mutex> lock(poolMutex);

    auto dbInstance = std::move(pool.front());
    pool.pop();
    return dbInstance;
}

void DatabasePool::release(std::unique_ptr<Database>& dbInstance) {
    std::lock_guard<std::mutex> lock(poolMutex);
    pool.push(std::move(dbInstance));
}

DatabasePool &DatabasePool::getInstance(size_t initialSize) {
    std::lock_guard<std::mutex> lock(poolMutex);
    if (!instance) {
        instance = std::unique_ptr<DatabasePool>(new DatabasePool(initialSize));
    }
    return *instance;
}

#include <EnvironmentReader.h>

#include <DatabaseExceptions.h>
#include <fstream>
#include <EnvVarManager.h>
#include <iostream>

#include <Logger.h>

EnvironmentReader::EnvironmentReader() {
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto delimiterPos = line.find('=');
        line.erase(line.end() - 1);
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            EnvVarManager::set(key, value);
        }
    }
}

EnvironmentReader &EnvironmentReader::getEnvReader() {
    static EnvironmentReader envReader;
    return envReader;
}

std::string EnvironmentReader::getConnString() {
    auto &logger = Logger::getInstance();
    if (EnvVarManager::get("DB_HOST").empty()) {
        logger.log(LogLevel::LOG_ERROR, "DB_HOST not set");
        throw EnvironmentVariableNotFound("Environment variable DB_HOST is not set");
    }
    if (EnvVarManager::get("DB_NAME").empty()) {
        logger.log(LogLevel::LOG_ERROR, "DB_NAME not set");
        throw EnvironmentVariableNotFound("Environment variable DB_NAME is not set");
    }
    if (EnvVarManager::get("DB_USER").empty()) {
        logger.log(LogLevel::LOG_ERROR, "DB_USER not set");
        throw EnvironmentVariableNotFound("Environment variable DB_USER is not set");
    }
    if (EnvVarManager::get("DB_PASSWORD").empty()) {
        logger.log(LogLevel::LOG_ERROR, "DB_PASSWORD not set");
        throw EnvironmentVariableNotFound(
            "Environment variable DB_PASSWORD is not set");
    }
    if (EnvVarManager::get("DB_PORT").empty()) {
        logger.log(LogLevel::LOG_ERROR, "DB_PORT not set");
        throw EnvironmentVariableNotFound("Environment variable DB_PORT is not set");
    }

    std::string connString =
            "dbname=" + EnvVarManager::get("DB_NAME") + " user=" +
            EnvVarManager::get("DB_USER")
            + " password=" + EnvVarManager::get("DB_PASSWORD") + " host="
            + EnvVarManager::get("DB_HOST") + " port=" + EnvVarManager::get("DB_PORT");
    logger.log(LogLevel::INFO, "Connection string set");
    return connString;
}

#include "EnvironmentReader.h"
#include <fstream>
#include "../Database/Database.h"
#include "../Utils/EnvVarManager.h"

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
            EnvVarManager::set(key,value);
        }
    }
}

EnvironmentReader &EnvironmentReader::getEnvReader() {
    static EnvironmentReader envReader;
    return envReader;
}

std::string EnvironmentReader::getConnString() {
    if (EnvVarManager::get("DB_HOST").empty())
        throw std::invalid_argument("Environment variable DB_HOST is not set");
    if (EnvVarManager::get("DB_NAME").empty())
        throw std::invalid_argument("Environment variable DB_NAME is not set");
    if (EnvVarManager::get("DB_USER").empty())
        throw std::invalid_argument("Environment variable DB_USER is not set");
    if (EnvVarManager::get("DB_PASSWORD").empty())
        throw std::invalid_argument(
            "Environment variable DB_PASSWORD is not set");
    if (EnvVarManager::get("DB_PORT").empty())
        throw std::invalid_argument("Environment variable DB_PORT is not set");
    std::string connString =
            "dbname=" + EnvVarManager::get("DB_NAME") + " user=" +
                EnvVarManager::get("DB_USER")
            + " password=" + EnvVarManager::get("DB_PASSWORD") + " host="
            + EnvVarManager::get("DB_HOST") + " port=" + EnvVarManager::get("DB_PORT");
    return connString;
}

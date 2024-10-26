#include "EnvironmentReader.h"
#include <fstream>

#include "../Database/Database.h"
EnvironmentReader::EnvironmentReader() {
    std::ifstream file(filePath);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Skip empty lines and comments
        auto delimiterPos = line.find('=');
        line.erase(line.end() - 1);
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            envMap[key] = value;
        }
    }
}

EnvironmentReader &EnvironmentReader::getEnvReader() {
    static EnvironmentReader envReader;
    return envReader;
}

std::string EnvironmentReader::getConnString() {
    if (!envMap.contains("DB_HOST"))
        throw std::invalid_argument("Environment variable DB_HOST is not set");
    if (!envMap.contains("DB_NAME"))
        throw std::invalid_argument("Environment variable DB_NAME is not set");
    if (!envMap.contains("DB_USER"))
        throw std::invalid_argument("Environment variable DB_USER is not set");
    if (!envMap.contains("DB_PASSWORD"))
        throw std::invalid_argument(
            "Environment variable DB_PASSWORD is not set");
    if (!envMap.contains("DB_PORT"))
        throw std::invalid_argument("Environment variable DB_PORT is not set");
    std::string connString = "dbname=" + envMap["DB_NAME"] + " user=" + envMap["DB_USER"] + " password=" + envMap[
                                 "DB_PASSWORD"] + " host=" + envMap["DB_HOST"] + " port=" + envMap["DB_PORT"];
    return connString;
}

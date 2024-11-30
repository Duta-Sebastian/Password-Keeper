#include "EnvVarManager.h"
#include <iostream>
std::string EnvVarManager::get(const std::string & varKey) {
    return getEnv(varKey);
}

int EnvVarManager::set(const std::string & varKey, const std::string & varValue) {
    return setEnv(varKey, varValue);
}

int EnvVarManager::unset(const std::string & varKey) {
    return unsetEnv(varKey);
}

std::string EnvVarManager::getEnv(const std::string & varKey) {
    const char* value = getenv(varKey.c_str());
    return value ? std::string(value) : "";
}

int EnvVarManager::setEnv(const std::string & varKey, const std::string & varValue) {
#if defined(_WIN32) || defined(_WIN64)
    return SetEnvironmentVariable(varKey.c_str(), varValue.c_str()) != 0;
#else
    return setenv(varKey.c_str(), varValue.c_str(), 1) == 0;
#endif
}

int EnvVarManager::unsetEnv(const std::string & varKey) {
#if defined(_WIN32) || defined(_WIN64)
    return SetEnvironmentVariable(varKey.c_str(), NULL) != 0;
#else
    return unsetenv(varKey.c_str()) == 0;
#endif
}

#include "DatabaseExceptions.h"

DatabaseExceptions::DatabaseExceptions(std::string message) : message(std::move(message)) {}

const char *DatabaseExceptions::what() const noexcept {
    return message.c_str();
}

FailedToCommit::FailedToCommit(const std::string &message) :
    DatabaseExceptions(std::move("Failure to commit work to database!\n"+message)) {}

FailedToOpen::FailedToOpen(const std::string &)
    : DatabaseExceptions(std::move("Failed to open database!\n"+message)) {}

EnvironmentVariableNotFound::EnvironmentVariableNotFound(const std::string &)
    : DatabaseExceptions(std::move("Environment variable not found!\n"+message)) {}

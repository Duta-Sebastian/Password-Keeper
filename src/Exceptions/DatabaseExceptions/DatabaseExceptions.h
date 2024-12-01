#ifndef DATABASEEXCEPTIONS_H
#define DATABASEEXCEPTIONS_H

#include <exception>
#include <string>


class DatabaseExceptions : public std::exception{
protected:
    std::string message;
public:
    explicit DatabaseExceptions(std::string);

    const char* what() const noexcept override;
};

class FailedToCommit final : public DatabaseExceptions {
public:
    explicit FailedToCommit(const std::string &);
};

class FailedToOpen final : public DatabaseExceptions {
public:
    explicit FailedToOpen(const std::string &);
};

class EnvironmentVariableNotFound final : public DatabaseExceptions {
public:
    explicit EnvironmentVariableNotFound(const std::string &);
};

#endif //DATABASEEXCEPTIONS_H

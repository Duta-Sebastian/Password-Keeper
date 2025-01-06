#ifndef ACCOUNTEXCEPTIONS_H
#define ACCOUNTEXCEPTIONS_H
#include <string>


class AccountExceptions : public std::exception {
protected:
     std::string message;

public:
     explicit AccountExceptions(std::string);

     const char *what() const noexcept override;
};

class AccountTypeExceptions final : public AccountExceptions {
public:
     explicit AccountTypeExceptions(const std::string &);
};


#endif //ACCOUNTEXCEPTIONS_H

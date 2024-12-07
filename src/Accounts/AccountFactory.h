#ifndef ACCOUNTFACTORY_H
#define ACCOUNTFACTORY_H

#include <map>
#include <memory>

#include <Account.h>
#include <AccountType.h>

class AccountFactory {
public:
    static std::shared_ptr<Account> accountFactory(AccountType, std::map<std::string, std::string>);
};


#endif //ACCOUNTFACTORY_H
